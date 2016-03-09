#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
template <class T>
class Node {
    public:
        T data;
        Node<T> *next;
};
template <class T>
class LinkedList {
    private:
        Node<T>* head;
        Node<T>* current;
    public:
        LinkedList() {
            head = NULL;
        }
        LinkedList(const LinkedList &L) {
            head = NULL;
            Node<T> *temp = L.head;
            while(temp != NULL) {
                insert(temp->data);
                temp = temp->next;
            }
        }
        ~LinkedList() {
            current = head;
            Node<T> *temp = current->next;
            while(current->next != NULL) {
                delete current;
                current = temp;
                temp = current->next;
            }
            delete current;
        }
        bool reset() {
            if(head == NULL) return false;
            else current = head;
            return true;
        }
        bool next() {
            if(current != NULL) current = current->next;
            if(current == NULL) return false;
            else return true;
        }
        //The user must use reset() and get() to iterate through the list
        T *get() {
            if(head == NULL || current == NULL) return NULL;
            return &(current->data);
        }
        bool insert(T data) {
            if(head == NULL) {
                head = new Node<T>();
                head->data = data;
                current = head;
            }
            else {
                while(current->next != NULL) {
                    current = current->next;
                }
                current->next = new Node<T>();
                current = current->next;
                current->data = data;
            }
            return true;
        }
        bool remove(){
            if(head == NULL) {return false;}
            else if(head == current) {
                Node<T>* temp = current->next;
                delete head;
                head = temp;
                current = temp;
            }
            else {
                Node<T>* temp = current;
                for(current = head; current->next != temp; current = current->next);
                current->next = current->next->next;
                delete temp;
            }
            return true;

        }
};
#endif
