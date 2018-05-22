/* Copyright 2018 Austin Ward */
#ifndef AUSTIN_WARD_MAP
#define AUSTIN_WARD_MAP


#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <deque>


namespace cs540 {
  template<typename Key_T, typename Mapped_T>
  class Map {
    private:
      class Node;
      class Node_base;
      size_t height_;
      size_t total_;
      Node_base* head_;


    public:
      class Iterator;
      class ConstIterator;
      class ReverseIterator;
      using ValueType = std::pair<const Key_T, Mapped_T>;


      Map() : height_(2), total_(0) {
        head_ = new Node_base(height_);
        for (size_t i = 0; i < head_->next.capacity(); i++) {
          head_->next[i] = static_cast<Node*> (head_);
          head_->prev[i] = static_cast<Node*> (head_);
        }
      }


      Map(std::initializer_list<ValueType> list) : Map() {
        for (auto v : list) this->insert(v);
      }


      Map(const Map &m) : Map() {
        Node* cur = static_cast<Node*> (m.head_)->next[0];
        while (cur != m.head_) {
          this->insert(cur->data_);
          cur = cur->next[0];
        }
      }


      ~Map() {
        Node* c = (static_cast<Node*> (head_))->next[0];
        Node* n = c->next[0];
        for (; c != head_; n = c->next[0]) {
          delete c;
          c = n;
        }
        delete head_;
        head_ = NULL;
      }


      Map &operator=(const Map &m) {
        Map<Key_T, Mapped_T> *new_m = new Map<Key_T, Mapped_T>(m);
        this->clear();
        Node* cur = static_cast<Node*> (new_m->head_)->next[0];
        while (cur != new_m->head_) {
          this->insert(cur->data_);
          cur = cur->next[0];
        }
        delete new_m;
        return *this;
      }


      Mapped_T &operator[](const Key_T &key) {
        try {
          return this->at(key);
        } catch (std::out_of_range) {
          this->insert({key, Mapped_T{}});
          return this->at(key);
        }
      }


      ValueType &operator()(const size_t idx) {
        Node* cur = static_cast<Node*> (head_)->next[0];
        size_t i = 0;
        for (; i < idx && cur != head_; i++, cur = cur->next[0]);
        return cur->data_;
      }


      friend
      bool operator==(const Map &m1, const Map &m2) {
        if (m1.total_ != m2.total_) return false;
        Node *temp = m1.head_->next[0];
        for(; temp != m1.head_; temp = temp->next[0]) {
          try {
            if (!(m2.at(temp->data_.first) == temp->data_.second) )
              return false;
          } catch (std::out_of_range) {
            return false;
          }
        }
        return true;
      }


      friend
      bool operator!=(const Map &m1, const Map &m2) {
        return !(m1 == m2);
      }


      friend
      bool operator<(const Map &m1, const Map &m2) {
        if (m1.total_ < m2.total_) return true;
        else if (m1.total_ > m2.total_) return false;
        Node t1 = m1.head_->next[0];
        Node t2 = m2.head_->next[0];
        for(; t1 != m1.head_; t1 = t1->next[0], t2 = t2->next[0]) {
          if (t2->data_.first < t1->data_.first || 
              t2->data_.second < t1->data_.second)
            return false;
        }
        return true;
      }


      Iterator begin() {
        return Iterator(static_cast<Node *> (head_->next[0]));
      }


      Iterator end() {
        return Iterator(static_cast<Node*> (head_));
      }


      ConstIterator begin() const {
        return ConstIterator(static_cast<Node *> (head_->next[0]));
      }


      ConstIterator end() const {
        return ConstIterator(static_cast<Node*> (head_));
      }


      ReverseIterator rbegin() {
        return ReverseIterator(static_cast<Node*> (head_->prev[0]));
      }


      ReverseIterator rend() {
        return ReverseIterator(static_cast<Node *> (head_));
      }


      ConstIterator find(const Key_T &key) const {
          size_t level = height_;
          Node* traverse = static_cast<Node*> (head_);
          while (level) {  // while not at the lowest level
            if (traverse->next[level] == head_ ||
                key < traverse->next[level]->data_.first ||
                key == traverse->next[level]->data_.first) {
              --level;
            } else {
              traverse = traverse->next[level];
            }
          }
          while (traverse->next[level] != head_) {
            if (traverse->next[level]->data_.first == key) {
              return ConstIterator(traverse->next[level]);
            } else {
              traverse = traverse->next[level];
            }
          }
          return this->end();
      }

      Iterator find(const Key_T &key) {
        size_t level = height_;
        Node* traverse = static_cast<Node*> (head_);
        while (level) {  // while not at the lowest level
          if (traverse->next[level] == head_ ||
              key < traverse->next[level]->data_.first ||
              key == traverse->next[level]->data_.first) {
            --level;
          } else {
            traverse = traverse->next[level];
          }
        }
        while (traverse->next[level] != head_) {
          if (traverse->next[level]->data_.first == key) {
            return Iterator(traverse->next[level]);
          } else {
            traverse = traverse->next[level];
          }
        }
        return this->end();
      }


      std::pair<Iterator, bool> insert(const ValueType v) {
        size_t level = height_;
        Node* traverse = static_cast<Node*> (head_);
        std::deque<Node*> pred_nodes;
        while (level) {  // while not at the lowest level
          if (traverse->next[level] == head_ ||
              v.first < traverse->next[level]->data_.first ||
              v.first == traverse->next[level]->data_.first) {
            pred_nodes.push_front(traverse);
            --level;
          } else {
            traverse = traverse->next[level];
          }
        }
        bool inserted = false;
        bool found = false;
        while (!inserted && !found) {
          if (traverse->next[level] == head_ || 
              v.first < traverse->next[level]->data_.first) {
            pred_nodes.push_front(traverse);
            insert_node(pred_nodes, new Node(v, select_level()));
            inserted = true;
            ++total_;
          } else if (v.first == traverse->next[level]->data_.first) {
            found = true;
          } else {
            traverse = traverse->next[level];
          }
        }
        return {Iterator(traverse->next[level]), inserted};
      }


      template <typename IT_T>
      void insert(IT_T range_beg, IT_T range_end) {
        for (auto it = range_beg; it != range_end; it++)
          this->insert((*it));
      }


      void erase(const Key_T &key) {
        size_t level = height_;
        Node* traverse = static_cast<Node*> (head_);
        while (level) {  // while not at the lowest level
          if (traverse->next[level] == head_ ||
              key < traverse->next[level]->data_.first ||
              key == traverse->next[level]->data_.first) {
            --level;
          } else {
            traverse = traverse->next[level];
          }
        }
        while (traverse->next[level] != head_) {
          if (traverse->next[level]->data_.first == key) {
            Node* temp = traverse->next[level];
            size_t h = temp->next.capacity();
            for (size_t i = 0; i < h; i++) {
              temp->next[i]->prev[i] = temp->prev[i];
              temp->prev[i]->next[i] = temp->next[i];
            }
            delete temp;
            --total_;
            return;
          } else {
            traverse = traverse->next[level];
          }
        }
        throw std::out_of_range ("That key does not exist.");
      }


      void erase(Iterator pos) {
        Node* temp = pos.cur;
        size_t h = temp->next.capacity();
        for (size_t i = 0; i < h; i++) {
          temp->next[i]->prev[i] = temp->prev[i];
          temp->prev[i]->next[i] = temp->next[i];
        }
        delete temp;
        --total_;
        return;
      }


      const Mapped_T &at(const Key_T &key) const {
        size_t level = height_;
        Node* traverse = static_cast<Node*> (head_);
        while (level) {  // while not at the lowest level
          if (traverse->next[level] == head_ ||
              key < traverse->next[level]->data_.first ||
              key == traverse->next[level]->data_.first) {
            --level;
          } else {
            traverse = traverse->next[level];
          }
        }
        while (traverse->next[level] != head_) {
          if (traverse->next[level]->data_.first == key) {
            return traverse->next[level]->data_.second;
          } else {
            traverse = traverse->next[level];
          }
        }
        throw std::out_of_range ("That key does not exist.");

      }


      Mapped_T &at(const Key_T &key) {
        size_t level = height_;
        Node* traverse = static_cast<Node*> (head_);
        while (level) {  // while not at the lowest level
          if (traverse->next[level] == head_ ||
              key < traverse->next[level]->data_.first ||
              key == traverse->next[level]->data_.first) {
            --level;
          } else {
            traverse = traverse->next[level];
          }
        }
        while (traverse->next[level] != head_) {
          if (traverse->next[level]->data_.first == key) {
            return traverse->next[level]->data_.second;
          } else {
            traverse = traverse->next[level];
          }
        }
        throw std::out_of_range ("That key does not exist.");
      }


      size_t size() { 
        return total_;
      }


      bool empty() {
        return !total_;
      }


      void clear() {
        Node* c = (static_cast<Node*> (head_))->next[0];
        Node* n = c->next[0];
        for (; c != head_; n = c->next[0]) {
          delete c;
          c = n;
        }
        delete head_;
        Map();
      }

      
      friend 
      bool operator!=(const Iterator &it1, const Iterator &it2) {
        return it1.cur != it2.cur;
      }


      friend 
      bool operator!=(const ConstIterator &it1, const ConstIterator &it2) {
        return it1.cur != it2.cur;
      }


      friend 
      bool operator!=(const ConstIterator &it1, const Iterator &it2) {
        return it1.cur != it2.cur;
      }


      friend 
      bool operator!=(const Iterator &it1, const ConstIterator &it2) {
        return it1.cur != it2.cur;
      }


      friend 
      bool operator==(const Iterator &it1, const Iterator &it2) {
        return it1.cur == it2.cur;
      }


      friend 
      bool operator==(const ConstIterator &it1, const ConstIterator &it2) {
        return it1.cur == it2.cur;
      }


      friend 
      bool operator==(const ConstIterator &it1, const Iterator &it2) {
        return it1.cur == it2.cur;
      }


      friend 
      bool operator==(const Iterator &it1, const ConstIterator &it2) {
        return it1.cur == it2.cur;
      }


      friend 
      bool operator!=(const ReverseIterator &it1, const ReverseIterator &it2) {
        return it1.cur != it2.cur;
      }


      friend 
      bool operator==(const ReverseIterator &it1, const ReverseIterator &it2) {
        return it1.cur == it2.cur;
      }


      class Iterator {
        private:
          Iterator(Node* n) : cur(n) {}
          friend 
          class Map<Key_T, Mapped_T>;


        public:
          Node* cur;


          Iterator& operator=(const Iterator &it) {
            this->cur = it.cur;
            return *this;
          }


          Iterator &operator++() {
            cur = cur->next[0];
            return *this;
          }


          Iterator operator++(int) {
            Iterator n = *this; 
            cur = cur->next[0];
            return n;
          }


          Iterator &operator--() {
            cur = cur->prev[0];
            return *this;
          }


          Iterator operator--(int) {
            Iterator n = *this; 
            cur = cur->prev[0];
            return n;
          }


          ValueType &operator*() const {
            return cur->data_;
          }


          ValueType *operator->() const {
            return &cur->data_;
          }
      };


      class ConstIterator {
        private:
          ConstIterator(Node* n) : cur(n) { }
          friend 
          class Map<Key_T, Mapped_T>;


        public:
          Node* cur;


          ConstIterator& operator=(const ConstIterator &it) {
            this->cur = it.cur;
            return *this;
          }


          ConstIterator &operator++() {
            cur = cur->next[0];
            return *this;
          }


          ConstIterator operator++(int) {
            ConstIterator n = *this; 
            cur = cur->next[0];
            return n;
          }


          ConstIterator &operator--() {
            cur = cur->prev[0];
            return *this;
          }


          ConstIterator operator--(int) {
            ConstIterator n = *this; 
            cur = cur->prev[0];
            return n;
          }


          const ValueType &operator*() const {
            return cur->data_;
          }


          const ValueType *operator->() const {
            return &cur->data_;
          }
      };


      class ReverseIterator {
        private:
          ReverseIterator(Node* n) : cur(n) {}
          friend 
          class Map<Key_T, Mapped_T>;


        public:
          Node* cur;


          ReverseIterator& operator=(const ReverseIterator &it) {
            this->cur = it.cur;
            return *this;
          }


          ReverseIterator &operator++() {
            cur = cur->prev[0];
            return *this;
          }


          ReverseIterator operator++(int) {
            ReverseIterator n = *this; 
            cur = cur->prev[0];
            return n;
          }


          ReverseIterator &operator--() {
            cur = cur->next[0];
            return *this;
          }


          ReverseIterator operator--(int) {
            ReverseIterator n = *this; 
            cur = cur->next[0];
            return n;
          }


          ValueType &operator*() const {
            return cur->data_;
          }


          ValueType *operator->() const {
            return &cur->data_;
          }
      };


    private: 
      size_t select_level() {
        size_t lvl = 0;
        while(flip()) ++lvl;
        return lvl;
      }


      bool flip() { 
        return ((float) rand()/(float) RAND_MAX) > .5; 
      }


      void insert_node(std::deque<Node*> &pred_nodes, Node* n) {
        size_t new_h = n->next.capacity();
        size_t s = (new_h > height_) ? height_ + 1 : new_h;
        if (new_h - 1 > height_) {
          head_->next.resize(new_h, nullptr);
          head_->prev.resize(new_h, nullptr);
          for (size_t i = height_ + 1; i < new_h; i++) {
            n->next[i] = static_cast<Node*> (head_);
            n->prev[i] = static_cast<Node*> (head_);
            head_->next[i] = n;
            head_->prev[i] = n;
          }
          height_ = new_h - 1;
        }
        for (size_t i = 0; i < s; i++) {
          n->next[i] = pred_nodes[i]->next[i];
          n->prev[i] = pred_nodes[i];
          pred_nodes[i]->next[i]->prev[i] = n;
          pred_nodes[i]->next[i] = n;
        }
      }


      class Node_base {
        public:
          std::vector<Node*> next;
          std::vector<Node*> prev;

          Node_base(size_t h) {
            next.resize(h + 1, nullptr);
            prev.resize(h + 1, nullptr);
          }
          Node_base* operator*() { return this; }
      };


      class Node : public Node_base {
        public:
          ValueType data_;

          Node(ValueType d, size_t h) : Node_base(h), data_(d) {};
          Node* operator*() { return this; }
      };
  };
}
#endif
