#ifndef DISTRIBUTIONS_H
#define DISTRIBUTIONS_H
#include <vector>
#include <random>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

// Type of Pedestrian Distribution
vector<int> generateTypeOfPedes(int num_samples, int total_value, int lower_bound, int upper_bound) {
    // Calculate mean and standard deviation
    double mean = static_cast<double>(total_value) / num_samples;
    double std_dev = (mean - lower_bound) / 3.0;

    // Create a random number generator with a normal distribution
    random_device rd;
    mt19937 generator(rd());
    normal_distribution<double> distribution(mean, std_dev);

    // Generate samples
    vector<int> samples(num_samples);
    for (int i = 0; i < num_samples; ++i) {
        double value = distribution(generator);
        samples[i] = clamp(static_cast<int>(round(value)), lower_bound, upper_bound);
    }

    // Shuffle the samples
    shuffle(samples.begin(), samples.end(), generator);

    // Swap the maximum value with the first element
    auto max_it = max_element(samples.begin(), samples.end());
    iter_swap(samples.begin(), max_it);

    // Print the sum of sample values
    cout << "Sum of sample values: " << accumulate(samples.begin(), samples.end(), 0) << endl;

    return samples;
}

vector<double> generateAge(int n, double min_value, double max_value) {

    // Initialize variables for mean and standard deviation
    double mean = (min_value + max_value) / 2.0;
    double std = (max_value - min_value) / 6.0;

    // Create a random number generator with a normal distribution
    default_random_engine generator;
    normal_distribution<double> distribution(mean,std);

    // Generate the sample
    vector<double> sample(n);
    for (int i = 0; i < n; ++i) {
        double value = distribution(generator);
        sample[i] = clamp(value, min_value, max_value);
    }

    // Round the values to one decimal place
    for (int i = 0; i < n; ++i) {
        sample[i] = round(sample[i] * 10) / 10.0;
    }

    // Return the mean and standard deviation of the sample as a struct
    return sample;
}

//normal distribution
double normalDistribution(int x, double mean, double stdDev) {
    double exponent = -(pow(x - mean, 2) / (2 * pow(stdDev, 2)));
    return (1 / (sqrt(2 * M_PI) * stdDev)) * exp(exponent);
}

//random normal distribution
double rand_normal(double mean, double stddev)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(mean, stddev);
    double output = dist(gen);
    return output;
}

float randomFloat(float lowerBound, float upperBound)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(lowerBound, upperBound);
    return dis(gen);
}

int randomNumber(int lowerBound,int upperBound) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(lowerBound,upperBound);

    int random_number = dis(gen);
    return random_number;
}

#endif