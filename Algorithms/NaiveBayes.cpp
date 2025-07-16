#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>
#include <set>

using namespace std;

// Type aliases for clarity
using FeatureVector = vector<string>;
using Dataset = vector<FeatureVector>;
using LabelVector = vector<string>;

class NaiveBayes {
    set<string> classes;
    unordered_map<string, int> classCounts;
    unordered_map<string, vector<unordered_map<string, int>>> featureCounts;
    int numFeatures = 0;
    int totalSamples = 0;

public:
    // Train the classifier
    void train(const Dataset& data, const LabelVector& labels) {
        totalSamples = data.size();
        if (totalSamples == 0) return;
        numFeatures = data[0].size();

        for (size_t i = 0; i < data.size(); ++i) {
            const string& label = labels[i];
            classes.insert(label);
            classCounts[label]++;

            for (int j = 0; j < numFeatures; ++j) {
                featureCounts[label].resize(numFeatures);
                featureCounts[label][j][data[i][j]]++;
            }
        }
    }

    // Predict the class for a sample
    string predict(const FeatureVector& sample) {
        double bestProb = -1e9;
        string bestClass;

        for (const auto& label : classes) {
            double logProb = log((double)classCounts[label] / totalSamples);

            for (int i = 0; i < numFeatures; ++i) {
                const string& val = sample[i];
                int count = featureCounts[label][i][val];
                int total = classCounts[label];
                // Laplace smoothing
                logProb += log((count + 1.0) / (total + featureCounts[label][i].size()));
            }

            if (logProb > bestProb) {
                bestProb = logProb;
                bestClass = label;
            }
        }

        return bestClass;
    }
};

int main() {
    Dataset data = {
        {"sunny", "hot", "high", "FALSE"},
        {"sunny", "hot", "high", "TRUE"},
        {"overcast", "hot", "high", "FALSE"},
        {"rainy", "mild", "high", "FALSE"},
        {"rainy", "cool", "normal", "FALSE"},
        {"rainy", "cool", "normal", "TRUE"},
        {"overcast", "cool", "normal", "TRUE"},
        {"sunny", "mild", "high", "FALSE"},
        {"sunny", "cool", "normal", "FALSE"},
    };

    LabelVector labels = {
        "no", "no", "yes", "yes", "yes", "no", "yes", "no", "yes"
    };

    NaiveBayes nb;
    nb.train(data, labels);

    FeatureVector test = {"sunny", "cool", "normal", "TRUE"};
    cout << "Prediction: " << nb.predict(test) << endl;

    return 0;
}
