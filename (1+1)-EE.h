//
// Created by andre on 5/15/22.
//

#ifndef _1_1__EE__1_1_EE_H_
#define _1_1__EE__1_1_EE_H_

#include <vector>
#include <stdexcept>
#include <fstream>
#include "rand.h"

/// Función a usar
/// \param x : punto x
/// \return f(x)
double function(const std::vector<double> &x){
  // f(x_1,x_2) = (4 - 2.1*x_1^2 + (x_1^4)/3)*x_1^2 + x_1*x_2 + (-4 + 4x_2^2)x_2^2
  return (4.0 - 2.1*x[0]*x[0] + ((x[0]*x[0]*x[0]*x[0])/3.0))*x[0]*x[0] + x[0]*x[1] + (-4.0 + 4.0*x[1]*x[1])*x[1]*x[1];
}

/// Buscar el óptimo dado un punto x de inicio, máximo de generaciones Gmax y restricciones tipo a_i <= x_i <= b_i en un arreglo constraints
/// \param Gmax : Número máximo de generaciones
/// \param x : Punto inicializado (número de variables n = x.size())
/// \param constraints : arreglo de restricciones tipo a_i <= x_i <= b_i {(a_1,b_1),...,(a_n,b_n)}
/// \param filename : nombre de archivo donde guardaremos
/// \return arreglo (x,f(x))
std::vector<std::pair<std::vector<double>, double>> onePOneEE(int Gmax, std::vector<double> &x, const std::vector<std::pair<double, double>> &constraints, std::string filename){
  std::vector<std::pair<std::vector<double>, double>> results;

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
  std::ofstream file(filename);
  results.emplace_back(x,f);

  // Impresión inicial
  // Imprimir al archivo
  file << "x=(";
  for(size_t index = 0; index < x.size(); ++index){
    file << std::to_string(x[index]) << ", "[index == x.size() - 1];
  }
  file << "), f(x)=" << std::to_string(f) << '\n';

  for (int t = 0; t <= Gmax;) {
    // Inicializar semilla e hijo
    initrandom(time(0));
    std::vector<double> xPrime(x.size(), 0.0);

    // Mutar al vector x
    for(size_t i = 0; i < xPrime.size(); ++i){
      xPrime[i] = x[i] + sigma[t] * N(0,1);
      // Seguir buscando x'_i que satisfaga las restricciones si no las cumplió anteriormente
      while(constraints[i].second < xPrime[i] || xPrime[i] < constraints[i].first){
        xPrime[i] = x[i] + sigma[t] * N(0,1);
      }
    }

    // Comparar x con x' y seleccionar el mejor
    double Fprime = function(xPrime);
    f = function(x);
    if(Fprime < f) {
      // Hijo reemplaza al padre y aumenta el contador de número de hijos exitosos
      x = xPrime;
      f = Fprime;

      freq += 1.0;
    }

    // Imprimir al archivo y agregar a resultados
    file << "x=(";
    for(size_t index = 0; index < x.size(); ++index){
      file << std::to_string(x[index]) << ", "[index == x.size() - 1];
    }
    file << "), f(x)=" << std::to_string(f) << '\n';
    results.emplace_back(x,f);

    // t = t+1 y modificamos sigma[t]
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

    // Modificación de ps
    if(t%(10*x.size()) == 0){
      ps = freq / (10.0*x.size());
      freq = 0.0;
    }
  }

  file.close();
  return results;
}

#endif //_1_1__EE__1_1_EE_H_
