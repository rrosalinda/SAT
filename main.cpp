#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>
using namespace std;
//"scores" object for future storage
struct mScores {
    int math;
    int eng;
    string states;
    int years;

    mScores(int _math, int _eng, string _states, int _years) {
        math = _math;
        eng = _eng;
        states = _states;
        years = _years;
    }
};

//makes a map of scores mapped to indices
map<int, mScores> makeMap(vector<int> math, vector<int> eng, vector<string> states, vector<int> years) {

    map<int, mScores> scores;

    for (int i = 0; i < math.size(); i++) {
        scores.emplace(i, mScores(math.at(i), eng.at(i), states.at(i), years.at(i)));
    }

    return scores;
}

void mapPrintStateAsc(map<int, mScores> scores) {

    int count = 0;
    int currId = 0;
    vector<bool> dupes(scores.size(), false);
    bool dupeCheck = false;

    for (int i = 0; i < scores.size(); i++) {
        mScores currSc = scores.at(0);
        for (auto &s : scores) {
            if (s.second.states <= currSc.states) {
                if (dupes[s.first] == true) {
                    dupeCheck = true;
                }
                if (!dupeCheck) {
                    currSc = s.second;
                    currId = s.first;
                }
                dupeCheck = false;
            }
        }
        dupes[currId] = true;
        cout << currSc.states << " " << currSc.math << " " << currSc.eng << " " << currSc.years << endl;
    }
}

void mapPrintStateDesc(map<int, mScores> scores) {

    int count = 0;
    int currId = 0;
    vector<bool> dupes(scores.size(), false);
    bool dupeCheck = false;

    for (int i = 0; i < scores.size(); i++) {
        mScores currSc = scores.at(0);
        for (auto& s : scores) {
            if (s.second.states >= currSc.states) {
                if (dupes[s.first] == true) {
                    dupeCheck = true;
                }
                if (!dupeCheck) {
                    currSc = s.second;
                    currId = s.first;
                }
                dupeCheck = false;
            }
        }
        dupes[currId] = true;
        cout << currSc.states << " " << currSc.math << " " << currSc.eng << " " << currSc.years << endl;
    }
}

void mapPrintScoreAsc(map<int, mScores> scores) {

    int count = 0;
    int currId = 0;
    vector<bool> dupes(scores.size(), false);
    bool dupeCheck = false;

    for (int i = 0; i < scores.size(); i++) {
        mScores currSc = scores.at(0);
        for (auto& s : scores) {
            if (s.second.eng + s.second.math <= currSc.eng + currSc.math) {
                if (dupes[s.first] == true) {
                    dupeCheck = true;
                }
                if (!dupeCheck) {
                    currSc = s.second;
                    currId = s.first;
                }
                dupeCheck = false;
            }
        }
        dupes[currId] = true;
        cout << currSc.states << " " << currSc.math << " " << currSc.eng << " " << currSc.years << endl;
    }
}

void mapPrintScoreDesc(map<int, mScores> scores) {

    int count = 0;
    int currId = 0;
    vector<bool> dupes(scores.size(), false);
    bool dupeCheck = false;

    for (int i = 0; i < scores.size(); i++) {
        mScores currSc = scores.at(0);
        for (auto& s : scores) {
            if (s.second.eng + s.second.math >= currSc.eng + currSc.math) {
                if (dupes[s.first] == true) {
                    dupeCheck = true;
                }
                if (!dupeCheck) {
                    currSc = s.second;
                    currId = s.first;
                }
                dupeCheck = false;
            }
        }
        dupes[currId] = true;
        cout << currSc.states << " " << currSc.math << " " << currSc.eng << " " << currSc.years << endl;
    }
}

void mapSearchStateAvg(map<int, mScores> scores, string state) {

    int stateCount = 0;

    for (auto& s : scores) {
        if (state == s.second.states) {
            stateCount++;
        }
    }

    if (stateCount == 0) {
        cout << "No valid entries for given state." << endl;
        return;
    }

    int count = 0;
    int currId = 0;
    vector<bool> dupes(scores.size(), false);
    vector<mScores> result;
    bool dupeCheck = false;

    for (int i = 0; i < stateCount; i++) {
        mScores currSc = scores.at(0);
        for (auto& s : scores) {
            if (s.second.states == state) {
                if (dupes[s.first] == true) {
                    dupeCheck = true;
                }
                if (!dupeCheck) {
                    currSc = s.second;
                    currId = s.first;
                }
                dupeCheck = false;
            }
        }
        dupes[currId] = true;

        if (result.empty()) {
            result.push_back(currSc);
        }
        else {
            result.at(0).eng += currSc.eng;
            result.at(0).math += currSc.math;

        }
        count++;
    }
    for (auto& s : result) {
        cout << "Average scores for " << state << " over " << count << " scores: " << result.at(0).eng/count << " English and " << result.at(0).math/count << " math." << endl;
    }
}

void mapSearchScores(map<int, mScores> scores, int score) {

    int count = 0;
    int currId = 0;
    vector<bool> dupes(scores.size(), false);
    vector<mScores> result;
    bool dupeCheck = true;
    bool found = true;

    while (found) {
        mScores currSc = scores.at(0);
        found = false;
        for (auto& s : scores) {
            if (s.second.eng + s.second.math == score) {
                if (dupes[s.first] == true) {
                    dupeCheck = true;
                }
                if (!dupeCheck) {
                    currSc = s.second;
                    currId = s.first;
                    found = true;
                }
                dupeCheck = false;
            }
        }
        if (!found)
            break;
        dupes[currId] = true;
        cout << currSc.states << " " << currSc.math << " " << currSc.eng << " " << currSc.years << endl;
    }
}

void mapSearchScoresBelowVal(map<int, mScores> scores, int score) {

    int count = 0;
    int currId = 0;
    vector<bool> dupes(scores.size(), false);
    vector<mScores> result;
    bool dupeCheck = true;
    bool found = true;

    while (found) {
        mScores currSc = scores.at(0);
        found = false;
        for (auto& s : scores) {
            if (s.second.eng + s.second.math < score) {
                if (dupes[s.first] == true) {
                    dupeCheck = true;
                }
                if (!dupeCheck) {
                    currSc = s.second;
                    currId = s.first;
                    found = true;
                }
                dupeCheck = false;
            }
        }
        if (!found)
            break;
        dupes[currId] = true;
        cout << currSc.states << " " << currSc.math << " " << currSc.eng << " " << currSc.years << endl;
    }
}

void mapSearchScoresAboveVal(map<int, mScores> scores, int score) {

    int count = 0;
    int currId = 0;
    vector<bool> dupes(scores.size(), false);
    vector<mScores> result;
    bool dupeCheck = true;
    bool found = true;

    while (found) {
        mScores currSc = scores.at(0);
        found = false;
        for (auto& s : scores) {
            if (s.second.eng + s.second.math > score) {
                if (dupes[s.first] == true) {
                    dupeCheck = true;
                }
                if (!dupeCheck) {
                    currSc = s.second;
                    currId = s.first;
                    found = true;
                }
                dupeCheck = false;
            }
        }
        if (!found)
            break;
        dupes[currId] = true;
        cout << currSc.states << " " << currSc.math << " " << currSc.eng << " " << currSc.years << endl;
    }
}

int main() {
    // vectors to store SAT data
    vector<int> mathScoresVec;
    vector<int> engScoresVec;
    vector<string> statesVec;
    vector<int> yearsVec;

    // open CSV file
    ifstream inFile;
    inFile.open("SAT_Scores.csv"); // csv file has to be in same directory as program

    // if file opened correctly
    if (inFile.is_open()){
        string line;
        getline(inFile,line); // reading titles

        while (getline(inFile,line)){
            string token; // token to hold variable value of interest
            istringstream stream(line);

            // read in math score into vector
            getline(stream,token,',');
            mathScoresVec.push_back(stoi(token));

            // read in eng score into vector
            getline(stream,token,',');
            engScoresVec.push_back(stoi(token));

            // read in state into vector
            getline(stream,token,',');
            statesVec.push_back(token);

            // read in year into vector
            getline(stream,token,',');
            yearsVec.push_back(stoi(token));
        }
    }
    // prompt user for Data Structure of Choice
    cout << "Welcome to the SAT Database" << endl;
    cout << "Select Data Structure to Proceed: " << endl;
    cout << "1) Database implemented using sets" << endl;
    cout << "2) Database implemented using maps" << endl;
    int dbChoice = 0;
    cin >> dbChoice;
    cout << endl;

    if (dbChoice == 1) {
        // set implementation
        set<string> statesSet; // create a set
        for (auto & i : statesVec){
            statesSet.insert(i); // add states to set, no duplicates
        }
        // vector of sets to hold the scores
        vector<set<int>> vecOfSetMath(statesSet.size());
        vector<set<int>> vecOfSetEng(statesSet.size());
        // add scores to set
        auto iterator = statesSet.begin();
        int index = 0;
        int count = 0;
        for (int i = 0; i < statesVec.size(); i++) {
            index = 0;
            for(;iterator != statesSet.end(); iterator++){
                if (statesVec[i] == *iterator){
                    count++;
                    vecOfSetMath[index].insert(mathScoresVec[i]);
                    vecOfSetEng[index].insert(engScoresVec[i]);
                }
                index++;
            }
            iterator = statesSet.begin();
        }
        int input1 = 0;
        while (input1 != 3) {
            // print main menu
            cout << "SAT Scores Database" << endl;
            cout << "1) Print" << endl;
            cout << "2) Search" << endl;
            cout << "3) Exit" << endl;

            cin >> input1;

            if (input1 == 1) {
                cout << "1) by state, ascending" << endl;
                cout << "2) by state, descending" << endl;
                cout << "3) by scores, ascending" << endl;
                cout << "4) by scores, descending" << endl;

                int input2;
                cin >> input2;

                if (input2 == 1 || input2 == 3) { // because sets are already sorted, states and scores are both sorted
                    auto iter = statesSet.begin();
                    index = 0;
                    for (; iter != statesSet.end(); iter++) {
                        cout << *iter << endl;
                        cout << "Math\tReading" << endl;

                        // checking size
                        cout << "Reading Size: " << vecOfSetMath[index].size() << endl;
                        cout << "Math Size: " << vecOfSetEng[index].size() << endl;

                        // check larger set
                        int mathSetSize = vecOfSetMath[index].size();
                        int engSetSize = vecOfSetEng[index].size();
                        int loop = mathSetSize;
                        if (mathSetSize < engSetSize)
                            loop = engSetSize;
                        auto iterMath = vecOfSetMath[index].begin();
                        auto iterEng = vecOfSetEng[index].begin();
                        for (; loop > 0; loop--) {
                            if (iterMath != vecOfSetMath[index].end()) {
                                cout << *iterMath << "\t\t";
                                *iterMath++;
                            } else {
                                cout << "   " << "\t\t";
                            }
                            if (iterEng != vecOfSetEng[index].end()) {
                                cout << *iterEng << endl;
                                *iterEng++;
                            } else {
                                cout << "   " << endl;
                            }
                        }
                    }
                }
                else if (input2 == 2) { // because sets are already sorted, states and scores are both sorted
                    auto iter = statesSet.rbegin();
                    index = statesSet.size()-1;
                    for (;iter != statesSet.rend(); iter++) { // to iterate in reverse
                        cout << *iter << endl;
                        cout << "Math\tReading" << endl;
                        auto iterMath = vecOfSetMath[index].begin();
                        auto iterEng = vecOfSetEng[index].begin();
                        for (;iterMath != vecOfSetMath[index].end(); iterMath++){
                            cout << *iterMath << "\t\t" << *iterEng << endl;
                            if(iterEng != vecOfSetEng[index].end())
                                iterEng++;
                        }
                        index--;
                    }
                    cout << endl;
                }
                else if (input2 == 4) { // because sets are already sorted, states and scores are both sorted
                    auto iter = statesSet.rbegin();
                    index = statesSet.size()-1;
                    for (;iter != statesSet.rend(); iter++) { // to iterate in reverse
                        cout << *iter << endl;
                        cout << "Math\tReading" << endl;
                        auto iterMath = vecOfSetMath[index].end();
                        auto iterEng = vecOfSetEng[index].end();
                        iterMath++;
                        iterEng++;
                        for (;iterMath != vecOfSetMath[index].begin(); iterMath--){
                            cout << *iterMath << "\t\t" << *iterEng << endl;
                            if(iterEng != vecOfSetEng[index].begin())
                                iterEng--;
                        }
                        index--;
                    }
                    cout << endl;
                }
            }
            else if (input1 == 2) {
                cout << "1) by state (view average)" << endl;
                cout << "2) by score (view states with those scores)" << endl;
                cout << "3) by score (view states with scores below given threshold)" << endl;
                cout << "4) by score (view states with scores above given threshold)" << endl;

                int input2;
                cin >> input2;

                if (input2 == 1){
                    cout << "Name of State: ";
                    string nameState;
                    cin >> nameState;
                    cout << endl;

                    int sumMath = 0;
                    int sumEng = 0;
                    bool found = false;

                    auto iter = statesSet.begin();
                    index = 0;
                    for (; iter != statesSet.end(); iter++) {
                        if (*iter == nameState){
                            found = true;
                            cout << nameState << endl;
                            auto iterMath = vecOfSetMath[index].begin();
                            auto iterEng = vecOfSetEng[index].begin();
                            for (;iterMath != vecOfSetMath[index].end(); iterMath++){
                                sumEng = sumEng + *iterEng;
                                sumMath = sumMath + *iterMath;
                                if(iterEng != vecOfSetEng[index].end())
                                    iterEng++;
                            }
                            break;
                        }
                        index++;
                    }
                    // calculate average
                    if (found) {
                        cout << "Math Average: " << double(sumMath) / double(vecOfSetMath[index].size()) << endl;
                        cout << "Reading Average: " << double(sumEng) / double(vecOfSetEng[index].size()) << endl;
                    }
                    else{
                        cout << nameState << " not found" << endl;
                    }
                    cout << endl;
                }
                else if (input2 == 2){
                    cout << "Enter Score: ";
                    int score;
                    cin >> score;
                    cout << endl;

                    set <string> statesWithScores;
                    auto iter = statesSet.begin();
                    index = 0;
                    for (; iter != statesSet.end(); iter++) {
                        auto iterMath = vecOfSetMath[index].begin();
                        auto iterEng = vecOfSetEng[index].begin();
                        for (;iterMath != vecOfSetMath[index].end(); iterMath++){
                            if (*iterMath == score || *iterEng == score){
                                statesWithScores.insert(*iter);

                                // cout << *iter << "\t" << *iterMath << "\t" << *iterEng << endl;
                            }
                            if(iterEng != vecOfSetEng[index].end())
                                iterEng++;
                        }
                        index++;
                    }
                    cout << "States with those scores" << endl;
                    if (statesWithScores.empty())
                        cout << "No states with those scores" << endl;
                    else {
                        iter = statesWithScores.begin();
                        for (; iter != statesWithScores.end(); iter++) {
                            cout << *iter << endl;
                        }
                    }
                    cout << endl;
                }
                else if (input2 == 3){
                    cout << "Enter Score: ";
                    int score;
                    cin >> score;
                    cout << endl;

                    set <string> statesWithScores;
                    auto iter = statesSet.begin();
                    index = 0;
                    for (; iter != statesSet.end(); iter++) {
                        auto iterMath = vecOfSetMath[index].begin();
                        auto iterEng = vecOfSetEng[index].begin();
                        for (;iterMath != vecOfSetMath[index].end(); iterMath++){
                            if (*iterMath < score && *iterMath != 1){ // account for varying set sizes because no duplicates in sets
                                statesWithScores.insert(*iter);
                            }
                            if (*iterEng < score && *iterEng != 1){ // account for varying set sizes
                                statesWithScores.insert(*iter);
                            }
                            if(iterEng != vecOfSetEng[index].end())
                                iterEng++;
                        }
                        index++;
                    }
                    cout << "States with scores below threshold" << endl;
                    if (statesWithScores.empty())
                        cout << "No states with scores below threshold" << endl;
                    else {
                        iter = statesWithScores.begin();
                        for (; iter != statesWithScores.end(); iter++) {
                            cout << *iter << endl;
                        }
                    }
                    cout << endl;
                }
                else if (input2 == 4){
                    cout << "Enter Score: ";
                    int score;
                    cin >> score;
                    cout << endl;

                    set <string> statesWithScores;
                    auto iter = statesSet.begin();
                    index = 0;
                    for (; iter != statesSet.end(); iter++) {
                        auto iterMath = vecOfSetMath[index].begin();
                        auto iterEng = vecOfSetEng[index].begin();
                        for (;iterMath != vecOfSetMath[index].end(); iterMath++){
                            if (*iterMath > score || *iterEng > score){
                                statesWithScores.insert(*iter);
                            }
                            if(iterEng != vecOfSetEng[index].end())
                                iterEng++;
                        }
                        index++;
                    }
                    cout << "States with scores above threshold" << endl;
                    if (statesWithScores.empty())
                        cout << "No states with scores above threshold" << endl;
                    else {
                        iter = statesWithScores.begin();
                        for (; iter != statesWithScores.end(); iter++) {
                            cout << *iter << endl;
                        }
                    }
                    cout << endl;
                }
            }
            else if (input1 == 3) {
                return 0;
            }
            else {
                cout << "Invalid Input" << endl;
            }
        }
    }
    if (dbChoice == 2){
        // map implementation
        int input1 = 0;
        while (input1 != 3) {
            cout << "SAT Scores Database" << endl;
            // print main menu
            cout << "1) Print" << endl;
            cout << "2) Search" << endl;
            cout << "3) Exit" << endl;

            cin >> input1;

            if (input1 == 1) {
                cout << "1) by state, ascending" << endl;
                cout << "2) by state, descending" << endl;
                cout << "3) by scores, ascending" << endl;
                cout << "4) by scores, descending" << endl;

                int input2;
                cin >> input2;

                // map implementations for options
                if (input2 == 1)
                    mapPrintStateAsc(makeMap(mathScoresVec, engScoresVec, statesVec, yearsVec));
                else if (input2 == 2)
                    mapPrintStateDesc(makeMap(mathScoresVec, engScoresVec, statesVec, yearsVec));
                else if (input2 == 3)
                    mapPrintScoreAsc(makeMap(mathScoresVec, engScoresVec, statesVec, yearsVec));
                else if (input2 == 4)
                    mapPrintScoreDesc(makeMap(mathScoresVec, engScoresVec, statesVec, yearsVec));
            } else if (input1 == 2) {
                cout << "1) by state (view average)" << endl;
                cout << "2) by scores (view states with those scores)" << endl;
                cout << "3) by scores (view scores below given threshold)" << endl;
                cout << "4) by scores (view scores above given threshold)" << endl;

                int input2;
                cin >> input2;

                cout << "Enter argument: ";
                string input3;
                cin >> input3;

                // map implementations for options
                if (input2 == 1)
                    mapSearchStateAvg(makeMap(mathScoresVec, engScoresVec, statesVec, yearsVec), input3);
                else if (input2 == 2)
                    mapSearchScores(makeMap(mathScoresVec, engScoresVec, statesVec, yearsVec), stoi(input3));
                else if (input2 == 3)
                    mapSearchScoresBelowVal(makeMap(mathScoresVec, engScoresVec, statesVec, yearsVec), stoi(input3));
                else if (input2 == 4)
                    mapSearchScoresAboveVal(makeMap(mathScoresVec, engScoresVec, statesVec, yearsVec), stoi(input3));
            } else if (input1 == 3) {
                return 0;
            } else {
                cout << "Invalid Input" << endl;
            }
        }
    }
    return 0;
}
