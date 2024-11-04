#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using std::vector, std::queue, std::cout, std::endl, std::string, std::find;

class State{
    private:
        vector<int> mState;//manzelka bude vzdy vedle manzela ve vectoru
        int boatSide; // strana lodi
        int numberOfPairs; // pocet paru
        //0: vlevo, 1: vpravo

        bool negateValues(vector<int> indexes, vector<State> &result){
            vector<int> temp = mState;
            for (size_t i = 0; i < indexes.size(); i++)
            {
                temp[indexes[i]] = !temp[indexes[i]];
            }
            if (isValid(temp))
            {
                result.push_back(State(temp, !boatSide));
                return true;
            }
            return false;
        }

    public:

    State(int NumberOfPairs){
        this->numberOfPairs = NumberOfPairs;
        this->boatSide = 0;
        this->mState = vector<int>(NumberOfPairs * 2, 0);
    }
    State( vector<int>& inState, int s){
        this->mState = inState;
        this->numberOfPairs = inState.size() / 2;
        this->boatSide = s;
    }
    bool isValid(){
        return this->isValid(mState);
    }
    bool isValid(const vector<int> input){
        //existuji povolene stavy: jenom zeny, jenom muzi, manželsky par spolu a kombinace techto stavu
        vector<int> strany = {0,0};
        //hodnota strany 1 = jenom zeny
        //hodnota strany 2 = jenom muzi
        //hodnota strany 0 = defaultni
        for (int i = 0; i < numberOfPairs*2; i+=2)
        {        
            if (input.at(i) == input.at(i+1))//manzelsky par je spolu - muzeme tuto iteraci ignorovat
            {
                continue; 
            }
            if (strany[input.at(i)] != 1 && strany[input.at(i)] != 0)//pokud je není na strane input.at(i) zena
            {
                return false;
            }
            if (strany[input.at(i+1)] != 2 && strany[input.at(i+1)] != 0)//pokud je není na strane input.at(i) muz
            {
                return false;
            }
            strany[input.at(i)] = 1;//na input.at(i) strane je zena
            strany[input.at(i+1)] = 2; // na input.at(i) je muz
        }
        return true;
    }
    bool isFinal() const {
        return mState == vector<int>(numberOfPairs * 2, 1);
    };

    vector<State> getPossibleChildren() {
        //mohou se spolu prepravovat jenom
        //zena
        //muz
        //zena zena
        //muz muz
        //zena muz ze stejneho paru
        vector<State> result;
        vector<int> trialChild;
        for (int i = 0; i < numberOfPairs*2; i++)
        {
            //muz nebo zena
            if (mState[i] == boatSide)
            {
                vector<int> indexes = {i};
                negateValues(indexes, result);
            }
            //muz muz nebo zena zena
            for (int j = i + 2; j < numberOfPairs * 2; j+=2) {
                
                if (mState[i] == boatSide && mState[j] == boatSide)
                {
                    vector<int> indexes = {i, j};
                    negateValues(indexes, result);
                }
            }
            //manzele
            if (i % 2 == 0 && mState[i] == boatSide && mState[i+1] == boatSide)
            {
                vector<int> indexes = {i, i+1};
                negateValues(indexes, result);
            }
        }
        return result;
    };
    bool operator==(const State other) const {
        return (mState == other.mState) && (boatSide == other.boatSide);
    }
    bool operator!=(const State other) const {
        return (mState != other.mState) && (boatSide != other.boatSide);
    }
};

int solveFroN(int n){
    queue<State> BFSqueue;
    vector<State> visitedStates;
    State initialState = State(n);

    visitedStates.push_back(initialState);
    BFSqueue.push(initialState);

    int counter = 0;
    bool finalStateFound = false;

    while (!BFSqueue.empty() && !finalStateFound)
    {
       counter++;
       int length = BFSqueue.size();
       for (int i = 0; i < length; i++)
       {
            State currentState = BFSqueue.front();
            BFSqueue.pop();
            vector<State> children = currentState.getPossibleChildren();
            for (State child : children)
            {
                if (find(visitedStates.begin(), visitedStates.end(), child) == visitedStates.end())
                {
                    visitedStates.push_back(child);
                    BFSqueue.push(child);
                }
                if (child.isFinal())
                {   
                    finalStateFound = true;
                    break;
                }
            }
        }
    }
    return counter;
}

int main(){
    for (int i = 2; i < 5; i++)
    {
        cout << i << " pairs - "  << solveFroN(i) << " transports" << endl;
    }
    return 0;
}