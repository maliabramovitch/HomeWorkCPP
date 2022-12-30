//
// Created by Mali Abramovitch on 20/12/2022.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include "World.h"
#include <string>

using namespace std;

World::World(char *config, char *first_generation, int gen) {
    generation = gen;
    ifstream configuration(config);
    ifstream firstGeneration(first_generation);
    if (!configuration || !firstGeneration) {
        cerr << "oopsi poopsi... file opening went wrong\n";
        ::exit(0);
    }
    string virusSize, pm, targett, populationSize, s;
    getline(configuration, virusSize);
    getline(configuration, pm);
    getline(configuration, targett);
    int *arr = new int[(stoi(virusSize))];
    stringstream ss1(targett);
    for (int i = 0; i < stoi(virusSize); ++i) {
        if (ss1.eof()) {
            cerr << "Invalid input.\n";
            exit(-1);
        }
        ss1 >> s;
        int n = stoi(s);
        arr[i] = n;
    }
    if (!ss1.eof()) {
        cerr << "Invalid input.\n";
        exit(-1);
    }
    this->target = new Virus("target", arr, stoi(virusSize), stoi(pm), nullptr);
    getline(firstGeneration, populationSize);
    population = new Population(stoi(populationSize), *this->target, stoi(virusSize), stoi(pm));
    this->familyIndexes = new int[stoi(populationSize)];
    for (int i = 0; i < stoi(populationSize); ++i) {
        this->familyIndexes[i] = 0;
        int *arr2 = new int[stoi(virusSize)];
        if (firstGeneration.eof()) {
            cerr << "Invalid input.\n";
        }
        string virus, name;
        getline(firstGeneration, virus);
        stringstream ss2(virus);
        ss2 >> name;
        for (int j = 0; j < stoi(virusSize); ++j) {
            if (ss2.eof()) {
                cerr << "Invalid input.\n";
            }
            ss2 >> s;
            int n = stoi(s);
            arr2[j] = n;
        }
        auto *v = new Virus(name, arr2, stoi(virusSize), this->population->getPm(), (familyIndexes + i));
        v->calculateErrorIndex(target);
        this->population->setVirus(i, *v);
    }
    population->insertionSort();
    
}

__attribute__((unused)) World::World(World &other) {
    this->generation = other.generation;
    this->population = new Population(*other.population);
    this->target = new Virus(target->getSize(), population->getPm());
    this->target = other.target;
    this->familyIndexes = other.familyIndexes;
}

World::~World() {
    delete population;
    delete[] familyIndexes;
}

World &World::operator=(World const &other) {
    if (this == &other)
        return *this;
    generation = other.generation;
    population = other.population;
    this->target = other.target;
    this->familyIndexes = other.familyIndexes;
    return *this;
}

void World::RunTheWorld() {
    for (int i = 0; i < generation; ++i) {
        if (population->getItsAMatch()) {
            cout << *population << '\n';
            cout << *population->getTheBestVirusEver() << '\n';
            exit(0);
        }
        ++(*population);
    }
    cout << *population;
    cout << '\n';
    cout << *population->getTheBestVirusEver() << '\n';
}

