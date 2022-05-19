//
// Created by andre on 5/15/22.
//

#ifndef _1_1__EE__1_1_EE_H_
#define _1_1__EE__1_1_EE_H_

#include <vector>
#include <stdexcept>
#include <fstream>
#include "rand.h"

double function(const std::vector<double> &x){
  // f(x_1,x_2) = (4 - 2.1*x_1^2 + (x_1^4)/3)*x_1^2 + x_1*x_2 + (-4 + 4x_2^2)x_2^2
  return (4.0 - 2.1*x[0]*x[0] + ((x[0]*x[0]*x[0]*x[0])/3.0))*x[0]*x[0] + x[0]*x[1] + (-4.0 + 4.0*x[1]*x[1])*x[1]*x[1];
}

void onePOneEE(int Gmax, std::vector<double> &x, const std::vector<std::pair<double, double>> &constraints){
  // Checar errores
  if(x.size() != constraints.size())
    throw std::runtime_error("longitud del punto x no coincide con el número de restricciones");

  // Inicialización de variables, semilla y archivo
  double f = function(x);
  double ps = 0.0;
  double freq = 0.0;
  std::vector<double> sigma(Gmax + 2, 0.0);
  sigma[0] = 3.0;
  double c = 0.817;
  std::ofstream file("out3.txt");

  // Imprimir al archivo inicialmente
  file << "x=(";
  for(size_t index = 0; index < x.size(); ++index){
    file << std::to_string(x[index]) << ", "[index == x.size() - 1];
  }
  file << "), f(x)=" << std::to_string(f) << ", ps=" << std::to_string(ps) << '\n';

  for (int t = 0; t <= Gmax;) {
    // Inicializar semilla e hijo
    initrandom(time(0));
    std::vector<double> xPrime(x.size(), 0.0);

    // Mutar al vector x
    for(size_t i = 0; i < xPrime.size(); ++i){
      xPrime[i] = x[i] + sigma[t] * N(0,1);
      // Seguir buscando x'_i que satisfaga las restricciones
      while(constraints[i].second < xPrime[i] || xPrime[i] < constraints[i].first){
        xPrime[i] = x[i] + sigma[t] * N(0,1);
      }
    }

    // Comparar x con x' y seleccionar el mejor
    double Fprime = function(xPrime);
    f = function(x);
    if(Fprime < f) {
      x = xPrime;
      f = Fprime;

      // Hijo reemplaza al padre
      freq += 1.0;
    }

    // Imprimir al archivo
    file << "x=(";
    for(size_t index = 0; index < x.size(); ++index){
      file << std::to_string(x[index]) << ", "[index == x.size() - 1];
    }
    file << "), f(x)=" << std::to_string(f) << ", ps=" << std::to_string(ps) << '\n';

    // Modificar sigma[t]
    ++t;
    if(t%x.size() == 0){
      if(ps > 1.0/5.0){
        sigma[t] = sigma[t-x.size()]/c;
      } else if(ps < 1.0/5.0){
        sigma[t] = sigma[(size_t) round(t-c)]*c;
      } else {
        sigma[t] = sigma[t-x.size()];
      }
    } else {
      sigma[t] = sigma[t-1];
    }

    // Modificación de ps (aumentamos t en uno porque empezamos desde 0 que es la iteración 1, así sucesivamente)
    if(t%(10*x.size()) == 0){
      ps = freq / 10.0*x.size();
      freq = 0.0;
    }
  }

  file.close();
}

#endif //_1_1__EE__1_1_EE_H_
