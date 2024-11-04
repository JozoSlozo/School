#include <iostream>
#include <queue>
#include <vector>
#include <set>
using std::vector, std::queue, std::cout, std::endl, std::set;

class State{
    private:
        vector<int> mState;
        //koza - vlla - zeli - prevoznik
        //0: vlevo, 1: vpravo
    public:
    State(){
        mState = {0,0,0,0};
    }
    State( vector<int>& inState){
        mState = inState;
    }
    bool isFinal() const {
        vector<int> final_state = {1,1,1,1};
        return mState == final_state;
    };
    bool isValid(){
        if (mState[3] != mState[0] and (mState[0] == mState[2] or mState[0] == mState[1]))
            {
                return false;
            }
            return true;
    }
    vector<State> getPossibleChildren() {
        vector<State> result;
        vector<int> newstate = mState;
        newstate[3] =  (newstate[3] + 1) % 2;
        State actualState(newstate);

        if (actualState.isValid())
        {
            result.push_back(actualState);
        }
        for (int i = 0; i < 3; i++)
        {
            if (mState[i] == mState[3])
            {
                newstate = mState;
                newstate[3] =  (newstate[3] + 1) % 2;
                newstate[i] =  (newstate[i] + 1) % 2;
                State actualState(newstate);
                if (actualState.isValid())
                {
                    result.push_back(actualState);
                }
            }
        }
        return result;
    };
    std::string tostring() {
        std::string temp = "";
        vector<std::string> stat = {"Koza: ", ", Vlk: ", ", Zeli: ", ", Prevoznik: "};
        for (int i = 0; i < 4; i++)
        {
            temp.append(stat[i]);
            temp.append(mState[i] ? "R" : "L");
        }
        return temp;
    }
    bool operator<(const State other) const {
        return mState < other.mState;
    }
};

int main(){
    std::queue<State> BFSqueue;
    std::set<State> visitedStates;
    State initialState;
    visitedStates.insert(initialState);
    BFSqueue.push(initialState);
    int counter = 0;
    bool finalStateFound = false;
    while (!BFSqueue.empty())
    {
       counter++;
       size_t length = BFSqueue.size();
       for (int i = 0; i < length; i++)
       {
            State currentState = BFSqueue.front();
            BFSqueue.pop();
            vector<State> children = currentState.getPossibleChildren();
            for (State child : children)
            {
                if (visitedStates.find(child) != visitedStates.end())
                {
                    continue;
                }
                
                if (child.isFinal())
                {   
                    finalStateFound = true;
                    break;
                }
                visitedStates.insert(child);
                BFSqueue.push(child);
            }
            
       }
       if (finalStateFound)
       {
            break;
       }    
    }
    cout << "pocet prevozu " << counter << endl;
    return 0;
}