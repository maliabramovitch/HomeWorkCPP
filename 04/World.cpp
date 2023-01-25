//
// Created by Mali Abramovitch on 08/01/2023.
//

#include "World.h"
#include "Papillomavirus.h"
#include "Lentivirus.h"
#include "Mimivirus.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


World::World(char *config, char *first_generation, int gen) {
    generation = gen;
    ifstream configuration(config);
    ifstream firstGeneration(first_generation);
    if (!configuration || !firstGeneration) {
        cerr << "oopsi poopsi... file opening went wrong\n";
        ::exit(-1);
    }
    string virusSize, targett, populationSize, s;
    char p;
    getline(configuration, virusSize);
    getline(configuration, targett);
    int *arr = new int[(stoi(virusSize))];
    stringstream ss1(targett);
    for (int i = 0; i < stoi(virusSize); ++i) {
        if (ss1.eof()) {
            invalidInput();
        }
        ss1 >> s;
        int n = stoi(s);
        arr[i] = n;
    }
    if (!ss1.eof()) {
        invalidInput();
    }
    this->target = new Virus("target", arr, stoi(virusSize), 0, nullptr, 'T');
    getline(firstGeneration, populationSize);
    population = new PopulationQueue(this->target, stoi(virusSize), stoi(populationSize));
    this->familyIndexes = new int[stoi(populationSize)];
    for (int i = 0; i < stoi(populationSize); ++i) {
        this->familyIndexes[i] = 0;
        int *arr2 = new int[stoi(virusSize)];
        if (firstGeneration.eof()) {
            invalidInput();
        }
        string virus, name;
        getline(firstGeneration, virus);
        stringstream ss2(virus);
        ss2 >> p;
        ss2 >> name;
        for (int j = 0; j < stoi(virusSize); ++j) {
            if (ss2.eof()) {
               invalidInput();
            }
            ss2 >> s;
            int n = stoi(s);
            arr2[j] = n;
        }
        Virus *v;
        switch (p) {
            case 'P':
                v = new Papillomavirus(name, arr2, stoi(virusSize), (familyIndexes + i));
                break;
            case 'L':
                v = new Lentivirus(name, arr2, stoi(virusSize), (familyIndexes + i));
                break;
            case 'M':
                v = new Mimivirus(name, arr2, stoi(virusSize), (familyIndexes + i));
                break;
            default:
                break;


        }
        population->addVirusToQueue(v);
    }
}

void World::RunTheWorld() {
    for (int i = 0; i < generation; ++i) {
        if (population->getItsAMatch()) {
            printpop();
            cout << '\n' << *population->getTheBestVirusEver() << '\n';
            exit(0);
        }
        ++(*population);
    }
    printpop();
    cout << '\n';
    cout << '\n' <<  *population->getTheBestVirusEver() << '\n';
}

World::~World() {
    delete population;
    delete [] familyIndexes;
}

__attribute__((unused)) World::World(World &other) {
    this->generation = other.generation;
    this->population = new PopulationQueue(*other.population);
    this->target = new Virus(*other.target);
    this->target = other.target;
    this->familyIndexes = other.familyIndexes;
}

World &World::operator=(const World &other) {
    if (this == &other)
        return *this;
    generation = other.generation;
    population = other.population;
    this->target = other.target;
    this->familyIndexes = other.familyIndexes;
    return *this;
}

void World::invalidInput() {
    cerr << "Invalid input.\n";
    exit(-1);
}

void World::printpop() {
    PopulationQueue* tmp = new PopulationQueue(target, 0, 0);
    for (int i = 0; i < population->getQueueSize(); ++i){
        tmp->addVirusToQueue(population->deQueueVirus());
    }
    cout << *tmp;
    delete tmp;
}
