#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <filesystem>
#include <regex>

using namespace std;
namespace fs = std::filesystem;

// --- System Info Helpers ---

string runCommand(const string& command) {
    string result;
    char buffer[128];
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) return "unknown";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    _pclose(pipe);
    return result;
}

// Remove newlines, extra spaces, and make fields CSV-safe
string sanitize(const string& input) {
    string cleaned = input;
    cleaned.erase(remove(cleaned.begin(), cleaned.end(), '\n'), cleaned.end());
    cleaned.erase(remove(cleaned.begin(), cleaned.end(), '\r'), cleaned.end());
    cleaned = regex_replace(cleaned, regex("\\s+"), " ");
    return cleaned;
}

string getCPUName() {
    return sanitize(runCommand("wmic cpu get Name /value | findstr Name"));
}

string getMemory() {
    return sanitize(runCommand("wmic memorychip get Capacity /value | findstr Capacity"));
}

string getDiskModel() {
    return sanitize(runCommand("wmic diskdrive get Model /value | findstr Model"));
}

// --- Sorting Helpers ---

string toLower(const string& s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

vector<string> readDataset(const string& filename) {
    vector<string> data;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open " << filename << endl;
        return data;
    }

    string word;
    while (file >> word) {
        data.push_back(word);
    }
    return data;
}

void bubbleSort(vector<string>& data) {
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data.size() - i - 1; ++j) {
            if (toLower(data[j]) > toLower(data[j + 1])) {
                swap(data[j], data[j + 1]);
            }
        }
    }
}

template<typename Func>
double timeSort(Func sortFunc, vector<string> data) {
    auto start = chrono::high_resolution_clock::now();
    sortFunc(data);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    return duration.count();
}

// --- Main Program ---

int main() {
    string cpu = getCPUName();
    string ram = getMemory();
    string disk = getDiskModel();

    vector<string> sizes = {"small", "medium", "large"};
    vector<string> paths = {
        "data/input/dataset_small.txt",
        "data/input/dataset_medium.txt",
        "data/input/dataset_large.txt"
    };

    fs::create_directories("data/output");
    ofstream outFile("data/output/times.csv");

    // Header for timing results
    outFile << "algorithm,size,time_ms\n";

    for (size_t i = 0; i < sizes.size(); ++i) {
        string sizeName = sizes[i];
        string path = paths[i];
        vector<string> original = readDataset(path);

        // std::sort
        double time_std = timeSort([](vector<string>& d) {
            sort(d.begin(), d.end(), [](const string& a, const string& b) {
                return toLower(a) < toLower(b);
            });
        }, original);
        outFile << "std_sort," << sizeName << "," << time_std << "\n";

        // bubble sort
        double time_bubble = timeSort(bubbleSort, original);
        outFile << "bubble_sort," << sizeName << "," << time_bubble << "\n";

        cout << "Sorted " << sizeName << " dataset with both algorithms.\n";
    }

    // Add a separator and then clean hardware info
    outFile << "\n";
    outFile << "cpu,memory,disk\n";
    outFile << "\"" << cpu << "\",\"" << ram << "\",\"" << disk << "\"\n";

    outFile.close();
    cout << "✅ Execution times saved to data/output/times.csv\n";
    return 0;
}
