#include <bits/stdc++.h>
#include "Random.h"

const double MUTATION_RATE = 0.01f;

using namespace std;

char get_char() {
    char alphabets[27];
    for (int i = 0; i < 26; i++) {
        alphabets[i] = (char)(i+97);
    }
    alphabets[26] = ' ';
    return(alphabets[Random::next_range(0, 26)]);
}

class DNA {
    string m_s;
    float m_fitness = 0.0f;
    public: 

    DNA (int target_length) {
        for (int i = 0; i < target_length; i++) {
            m_s += get_char();
        }
    }

    DNA (DNA& ParentA, DNA ParentB, int targetlen) {
        int partition = Random::next_range(1, targetlen-2);
        for (int i = 0; i < partition; i++) {
            m_s += ParentA.m_s[i];
        }
        for (int i = partition; i < targetlen; i++) {
            m_s += ParentB.m_s[i];
        }
    }


    float get_fitness(string& target, int target_len) {
        m_fitness = 0.0f;
        for (int i = 0; i < target_len; i++) {
            if (m_s[i] == target[i]) {
                m_fitness+= 10.0;
            }
            for (char c : target) {
                if(c == m_s[i]) {
                    m_fitness++;
                    break;
                }
            }
        }
        return (m_fitness/(target_len + (10.0*target_len)));
    }

    bool IsItTarget (string& target) {
        if (m_s == target) {
            return true;
        }
        return false;
    }

    void mutate() {
        int len = m_s.length();
        for (int i = 0; i < len; i++) {
            if(Random::next_bool(MUTATION_RATE)) {
                m_s[i] = get_char();
            }
        }
    }

    void print() {
        cout << m_s << '\n';
    }
};


int main() {
    string target;
    getline(cin, target);
    int len = target.length();
    int population_length = 150;

    bool found_target = false;
    vector<DNA> population;
    for (int i = 0; i < population_length; i++) {
        population.emplace_back(len);
        population[i].print();
        found_target = population[i].IsItTarget(target);
        if(found_target) {
            cout << "FOUND!!!\n";
            break;
        }
    }
    if(found_target) 
        return 0;
    
    while(!found_target) {
        vector<DNA> mating_pool;
        for (DNA x : population) {
            int n = x.get_fitness(target, len)*100;
            for (int i = 0; i < n; i++) {
                mating_pool.emplace_back(x);
            }
        }
        int total_breeders = mating_pool.size();
        for (int i = 0; i < population_length; i++) {
            DNA parentA = mating_pool[Random::next_range(0, total_breeders-1)];
            DNA parentB = mating_pool[Random::next_range(0, total_breeders - 1)];
            DNA child {parentA, parentB, len};
            found_target = child.IsItTarget(target);
            if(found_target)  {
                child.print();
                break;
            }         
            child.mutate();
            population[i] = child;
            found_target = child.IsItTarget(target);
            child.print();
            if (found_target) {
                break;
            }   
        }
        if(found_target) {
            cout << "FOUND!\n";
            break;
        }
    }
    if(found_target) 
        return 0;

    return 0;
}

