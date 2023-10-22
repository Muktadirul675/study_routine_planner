#include<iostream>
#include<vector>

using namespace std;

 struct Subject{
    string name;
    int lectures;
} ;


int classes_left(struct Subject  list[], int size){
    int due = 0;
    for(int i=0;i<size;i++){
        int lectures = list[i].lectures;
        if(lectures){due++;}
    }
    return due;
}

int findLowestIndex(vector<vector<string>> list, int size){
//cout << "finding";
    int index = 0;
    int lowest = list[0].size();
    for(int i=0;i<size;i++){
    //cout << "LOOP";
        int el = list[i].size();
        if(el < lowest){
            lowest = el;
            index = i;
        }
    }
    //cout << "found" << lowest  <<" " <<  index << endl;
    return index;
}


int main(){
    int  totalSubjects;
    cout << "Number of subjects: " ;
    cin >> totalSubjects;
    struct Subject list[totalSubjects];
    cout << "Subject - Lectures (By priority)\n" ;
    int total_classes = 0;
    for(int i=0;i<totalSubjects;i++){
        int num; string name;
        cout << i+1 <<". ";
        cin >> name; cin >> num;
        struct Subject s;
        s.name = name;
        s.lectures = num;
        total_classes += num;
        list[i] = s;
    }
    
    cout << "Your given input: \n" << endl;
    for(int i=0;i<totalSubjects;i++){
        cout << list[i].name << " " << list[i].lectures << endl;
    }
    cout << endl;
    
    vector<vector<string>> day = {{},{},{},{},{},{},{}};
    int  perDayLectures[totalSubjects];
    for(int i=0;i<totalSubjects; i++){
        perDayLectures[i] = list[i].lectures / 7;
    }
    
            for(int i=0;i<7;i++){
                vector<string> oneDayLectures;
                for(int j=0;j<totalSubjects;j++){
                    if(!(list[j].lectures <= 0)){
                     int daily_lecture = list[j].lectures / 7;
                     if(daily_lecture==0){daily_lecture=1;}
                        for(int k=0; k<daily_lecture;k++){
                       //cout << "pushing back " << list[j].name << "\n"<<endl;
                           int indexToPush = findLowestIndex(day,7);
                            day[indexToPush].push_back(list[j].name);
                            list[j].lectures--;
                            total_classes--;
                        }
                     }
                }
                //day[i].push_back(oneDayLectures);
                if(i == 6){
                    if(total_classes){i=-1;}
                }
            }
    
    int day_of_week = 0;
    for(auto i=day.begin(); i != day.end(); ++i){
    cout << day_of_week+1 << ". " ;
        for(auto j=i->begin(); j != i->end(); ++j){
            cout << *j << "\t" ;
        }
        cout << endl;
        day_of_week++;
    }
    
    return 0;
    }
    
    
