#include <bits/stdc++.h>

#include "yaml-cpp/yaml.h"

#define endl '\n'

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    YAML::Node config = YAML::LoadFile("data/settings.yaml");

    cout << "Fullscreen: " << config["fullscreen"] << endl;
    cout << "Show hitboxes: " << config["show_hitboxes"] << endl;


    return 0;
}