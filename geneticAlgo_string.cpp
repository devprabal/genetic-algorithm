#include <bits/stdc++.h>
using namespace std;
int population_size = 100;
string target_string = "Hello World!";
string genes = "abcdefghijklmnopqrstuvwxyz "
               "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890, .-;:_!\"#%&/()=?@${[]}";
int random_number(int lowerbound, int upperbound) {
  int range = upperbound - lowerbound;
  return lowerbound + rand() % (range + 1);
}
char random_genes_for_mutation() {
  return genes[random_number(0, genes.size() - 1)];
}
string make_chromosome() {
  int length = target_string.size();
  string gnome = "";
  for (int i = 0; i < length; i++) {
    gnome += random_genes_for_mutation();
  }
  return gnome;
}
class chromosome {
public:
  string gnome;
  int fitness;
  int calculate_fitness() {
    int fit = 0;
    for (int i = 0; i < target_string.size(); i++) {
      if (gnome[i] != target_string[i]) {
        fit++;
      }
    }
    return fit;
  }
  chromosome(string a_string) {
    gnome = a_string;
    fitness = calculate_fitness();
  }
  chromosome mate_and_reproduce(chromosome parent2) {
    string child_gnome = "";

    for (int i = 0; i < gnome.size(); i++) {
      int p = random_number(0, 100) / 100; // random probability
      if (p < 0.45)
        child_gnome += gnome[i];
      else if (p < 0.90)
        child_gnome += parent2.gnome[i];
      else
        child_gnome += random_genes_for_mutation();
    }
    return chromosome(child_gnome);
  }
};
bool operator<(chromosome individual1, chromosome individual2) {
  return individual1.fitness < individual2.fitness;
}
int main() {
  srand((unsigned)time(0));
  vector<chromosome> v;
  int generation = 0;
  // initial population
  for (int i = 0; i < population_size; i++) {
    v.push_back(chromosome(make_chromosome()));
  }
  bool found = false;
  while (!found) {
    sort(v.begin(), v.end());
    if (v[0].fitness == 0) {
      found = true;
      break;
    }
    vector<chromosome> new_generation;

    for (int i = 0; i < (0.1 * population_size); i++)
      new_generation.push_back(v[i]);
    for (int i = 0; i < (0.01 * population_size); i++)
      new_generation.push_back(v[v.size() / 2 - i]);
    for (int i = 0; i < (0.8 * population_size); i++) {
      chromosome parent1 = v[random_number(0, 49)];
      chromosome parent2 = v[random_number(0, 49)];
      chromosome child = parent1.mate_and_reproduce(parent2);
      new_generation.push_back(child);
    }
    v = new_generation;
    cout << "Generation " << generation << "\t";
    cout << "String " << v[0].gnome << "\t";
    cout << "Fitness " << v[0].fitness << "\n";
    generation++;
  }
  cout << "Generation " << generation << "\t";
  cout << "String " << v[0].gnome << "\t";
  cout << "Fitness " << v[0].fitness << "\n";
  cout << "Reached optimum solution\n";
  return 0;
}
