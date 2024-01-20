#include <bits/stdc++.h>

using namespace std;
#define ll long long;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(0);

    // res - trazeni broj
    int res;

    // v - 2D niz, prvi index broj koriscenih brojeva (max 6)
    // drugi index sadrzi dobijeni broj sa koriscenim brojevima i indexe koriscenih brojeva
    vector <vector<pair<int,set<int>>>> v(7);

    // close - vrednost najblizeg dobijenog broja
    // closeop - string koji cuva nacin dobijanja najblizeg broja
    int close = 0;
    string closeop = "";

    // op - 2D niz, za indexe op[i][j] cuva nacin dobijanja broja koji ima indexe v[i][j]
    vector <vector<string>> op(7);

    // unosenje inputa - 1. broj je trazeni broj
    // ostalih 6 su brojevi sa kojim se vrse operacije
    cin >> res;
    for(int i = 0;i < 6;i++){
        int x;
        cin >> x;
        v[1].push_back({x,{i}});
        op[1].push_back(to_string(x));
        // provjerava da li je jedan od unjetih brojeva jednak trazom broju
        if(x == res){
            cout << x << "=" << res << "\n";
            return 0;
        }
        // provjerava da li je najblizi broj za sad
        if(abs(res - x) < abs(res - close)){
            close = x;
            closeop = to_string(x) + "=" + to_string(x);
        }
    }

    // dvije for petlje koje odredjuju broj koriscenih brojeva prvog i drugog niza brojeva
    for(int fnum = 1;fnum < 6;fnum++){
        for(int snum = fnum;snum > 0;snum--){
            //posto imamo 6 ukupno cifara sve preko 6 ukupnih cifara je nemoguce
            if(fnum+snum > 6)continue;

            // dvije for petlje koje odredjuju brojeve koje koristimo
            // prva for petlja ima broj koji je dobijen pomocu fnum brojeva
            // druga ima broj koji je dobijen pomocu snum brojeva
            for(int i = 0;i < v[fnum].size();i++){
                for(int j = 0;j < v[snum].size();j++){
                    // provjera da li su ova 2 broja dobijena koristenjem barem jendog istog broja
                    bool good = true;
                    set <int> add = v[snum][j].second;
                    for(int usedind : v[fnum][i].second){
                        add.insert(usedind);
                        if(v[snum][j].second.count(usedind)){
                            good = false;
                            break;
                        }
                    }

                    if(!good)continue;

                    if(snum + fnum != 2 || j > i){
                        // operacija sabiranja
                        v[fnum+snum].emplace_back(v[fnum][i].first + v[snum][j].first,add);
                        op[fnum+snum].push_back('(' + op[fnum][i] + '+' + op[snum][j] + ')');
                        // da li je najblizi broj za sad
                        if(abs(v[fnum][i].first + v[snum][j].first - res) < abs(res - close)){
                            // da li je to trazeni broj
                            if(v[fnum][i].first + v[snum][j].first == res){
                                cout << '(' + op[fnum][i] + '+' + op[snum][j] + ')' + '=' + to_string(res);
                                return 0;
                            }else{
                                close = v[fnum][i].first + v[snum][j].first;
                                closeop = '(' + op[fnum][i] + '+' + op[snum][j] + ')';
                            }
                        }
                    }

                    if(v[fnum][i].first - v[snum][j].first > 0){
                        // operacija oduzimanja
                        v[fnum+snum].emplace_back(v[fnum][i].first - v[snum][j].first,add);
                        op[fnum+snum].push_back('(' + op[fnum][i] + '-' + op[snum][j] + ')');
                        if(abs(v[fnum][i].first - v[snum][j].first - res) < abs(res - close)){
                            if(v[fnum][i].first - v[snum][j].first == res){
                                cout << '(' + op[fnum][i] + '-' + op[snum][j] + ')' + '=' + to_string(res);
                                return 0;
                            }else{
                                close = v[fnum][i].first - v[snum][j].first;
                                closeop = '(' + op[fnum][i] + '-' + op[snum][j] + ')';
                            }
                        }
                    }

                    if(v[fnum][i].first % v[snum][j].first == 0 && v[snum][j].first != 1){
                        // operacija dijeljenja
                        v[fnum+snum].emplace_back(v[fnum][i].first / v[snum][j].first,add);
                        op[fnum+snum].push_back(op[fnum][i] + '/' + op[snum][j]);
                        if(abs(v[fnum][i].first / v[snum][j].first - res) < abs(res - close)){
                            if(v[fnum][i].first / v[snum][j].first == res){
                                cout << op[fnum][i] + '/' + op[snum][j] + '=' + to_string(res);
                                return 0;
                            }else{
                                close = v[fnum][i].first / v[snum][j].first;
                                closeop = op[fnum][i] + '/' + op[snum][j];
                            }
                        }
                    }

                    if(v[fnum][i].first != 1 &&  v[snum][j].first != 1){
                        // operacija mnozenja
                        v[fnum+snum].emplace_back(v[fnum][i].first * v[snum][j].first,add);
                        op[fnum+snum].push_back(op[fnum][i] + '*' + op[snum][j]);
                        if(abs(v[fnum][i].first * v[snum][j].first - res) < abs(res - close)){
                            if(v[fnum][i].first * v[snum][j].first == res){
                                cout <<op[fnum][i] + '*' + op[snum][j] + '=' + to_string(res);
                                return 0;
                            }else{
                                close = v[fnum][i].first * v[snum][j].first;
                                closeop = op[fnum][i] + '*' + op[snum][j];
                            }
                        }
                    }

                }
            }

        }
    }
    // ako je nemoguce naci trazeni broj izbacuje se najblizi
    cout << closeop + '=' + to_string(close) << "\n";
    return 0;
}