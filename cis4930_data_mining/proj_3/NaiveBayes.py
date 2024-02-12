import csv
import sys

from math import log


def clean_data(unclean_data, attrs):
    cleaned_data = []
    for row in unclean_data:
        temp = ['0'] * attrs
        for pair in row:
            parsed = pair.split(':')
            temp[int(parsed[0])-1] = parsed[1]
        cleaned_data.append(temp)
    return cleaned_data


def load_data(file):
    data_u = []
    labels = []
    max_attr = 0

    with open(file, newline='') as datafile:
        data_reader = csv.reader(datafile, delimiter=' ')

        for row in data_reader:
            # read data point
            data_u.append(row[1:])
            # read label
            labels.append(row[0])

            for pair in row[1:]:
                index = int((pair.split(':'))[0])
                if index > max_attr:
                    max_attr = index

    cleaned_data = clean_data(data_u, max_attr)

    return [(cleaned_data[i], labels[i]) for i in range(len(cleaned_data))], max_attr, set(labels)


def train(data, attrs, label_set):
    attr_freqs = []
    attr_probs = []
    label_freqs = dict(zip(label_set, [0]*len(label_set)))
    label_probs = {}
    set_size = len(data)

    # initialize lists with empty empty dictionary for each attribute
    for i in range(attrs):
        attr_freqs.append({})
        attr_probs.append({})

    # parse each datapoint and label tuple in training data
    # each tuple in data in format of ([datapoint], label)
    for pair in data:
        # update frequency dictionaries for each attribute in datapoint
        for i, attr in enumerate(pair[0]):
            if attr not in attr_freqs[i].keys():
                # initialize attribute freq dict
                (attr_freqs[i])[attr] = dict(
                    zip(label_set, [0]*len(label_set)))
                # initialize attribute probability dict
                (attr_probs[i])[attr] = dict(
                    zip(label_set, [0]*len(label_set)))
					
                ((attr_freqs[i])[attr])[pair[1]] = 1
            else:
                ((attr_freqs[i])[attr])[pair[1]] += 1

        label_freqs[pair[1]] += 1

    # calculate probabilities for each attribute's possible value
    for i, attr in enumerate(attr_freqs):
        for value in attr.keys():
            for label in ((attr_freqs[i])[value]).keys():
                ((attr_probs[i])[value])[label] = (
                    (attr_freqs[i])[value])[label]/label_freqs[label]

    # calculate probabilities for each label
    for label in label_freqs.keys():
        label_probs[label] = label_freqs[label] / set_size

    return attr_probs, label_probs


def test(data, label_set, attr_probs, label_probs):
    results = [0 for i in range(4)]
    predictions = dict(zip(label_set, [0]*len(label_set)))

    for pair in data:
        for label in predictions.keys():
            predictions[label] = log(label_probs[label])

        # update each label prediction with attribute probability
        for i, attr in enumerate(pair[0]):
            if attr in attr_probs[i].keys():
                for label in predictions.keys():
                    if ((attr_probs[i])[attr])[label] > 0:
                        predictions[label] += log(((attr_probs[i])[attr])[label])
                    else:
                        predictions[label] += float('-inf')
            else:
                for label in predictions.keys():
                    predictions[label] += float('-inf')

        # true positive
        if max(predictions, key=predictions.get) == pair[1] and pair[1] == '+1':
            results[0] += 1
        # false negative
        elif max(predictions, key=predictions.get) != pair[1] and pair[1] == '+1':
            results[1] += 1
        # false positive
        elif max(predictions, key=predictions.get) != pair[1] and pair[1] == '-1':
            results[2] += 1
        # true negative
        elif max(predictions, key=predictions.get) == pair[1] and pair[1] == '-1':
            results[3] += 1

    return results


if __name__ == '__main__':
	train_data, num_attrs, label_set = load_data(sys.argv[1])
	attr_probs, label_probs = train(train_data, num_attrs, label_set)
	results = test(train_data, label_set, attr_probs, label_probs)
	print(results[0], results[1], results[2], results[3])

	test_data, num_attrs, label_set = load_data(sys.argv[2])
	results = test(test_data, label_set, attr_probs, label_probs)
	print(results[0], results[1], results[2], results[3])
