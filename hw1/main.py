from decisionTree import DecisionTree
import sys

'''

fake_data = []

for i in range(2):
    fake_data.append({'wind': 0, 'foo': 0, 'Class': 0})
for i in range(6):
    fake_data.append({'wind': 0, 'foo': 0, 'Class': 1})
for i in range(3):
    fake_data.append({'wind': 1, 'foo': 0 , 'Class': 0})
    fake_data.append({'wind': 1, 'foo': 0, 'Class': 1})

target_attr = 'Class'
attrs = ['wind', 'foo']

dt = DecisionTree(fake_data, target_attr, attrs)

'''

with open(sys.argv[1] + "/training_set.csv") as f:
    training_data = []
    attrs = f.readline().replace('\n','').split(',')

    for line in f:
        item = {}
        values = line.replace('\n', '').split(',')
        for attr, value in zip(attrs, values):
            item[attr] = int(value)
        training_data.append(item)

    target_attr = attrs[-1]
    attrs = attrs[:-1]

with open(sys.argv[1] + "/validation_set.csv") as f:
    validate_data = []
    v_attrs = f.readline().replace('\n','').split(',')

    for line in f:
        item = {}
        values = line.replace('\n', '').split(',')
        for attr, value in zip(v_attrs, values):
            item[attr] = int(value)
        validate_data.append(item)

dt = DecisionTree(training_data, target_attr, attrs, validate_data)
root = dt.ID3()


with open(sys.argv[1] + "/test_set.csv") as f:
    test_data = []
    attrs = f.readline().replace('\n','').split(',')

    for line in f:
        item = {}
        values = line.replace('\n', '').split(',')
        for attr, value in zip(attrs, values):
            item[attr] = int(value)
        test_data.append(item)

correct = total = 0
for d in test_data:
    correct += dt.predict(root, d) == d[target_attr]
    total += 1
percent = 100 * correct/total

print("Predicted " + str(dt.accuracy(root, test_data)) + "% Correct")
