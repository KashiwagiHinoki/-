package main

import (
  "fmt"
  "math"
)


//recursive least squares method
//q -> fogetting coefficient
func rls(q float64, y, u []float64) (float64, float64){
  _u := make([]float64, len(u))
  for i := 0; i < len(u); i++{
    _u[i] = math.Pow(q, float64(len(u) - 1.0 - i)) * u[i]
  }
  _y := make([]float64, len(y))
  for i := 0; i < len(y); i++{
    _y[i] = math.Pow(q, float64(len(y) - 1.0 - i)) * y[i]
  }
  return lsm(_y, _u)
}

//least squares method
//u -> input, y -> output
func lsm(y, u []float64) (float64, float64){
  y_1 := make([]float64, len(y))
  y_1[0] = 0
  for i := 0; i < len(y) - 1; i++{
    y_1[i + 1] = y[i]
  }
  //a[0] - a[1] * x - a[2] * y = 0
  //a[3] - a[4] * x + a[5] * y = 0
  a := make([]float64, 6)
  for i := 0; i < len(y); i++{
    a[0] += y[i] * y_1[i]
    a[1] += y_1[i] * y_1[i]
    a[2] += y_1[i] * u[i]
    a[3] += u[i] * y[i]
    a[4] += u[i] * y_1[i]
    a[5] += u[i] * u[i]
  }
  alp := (a[2] * a[3] - a[0] * a[5])/(a[2] * a[4] - a[1] * a[5])
  bet := (a[0] * a[4] - a[1] * a[3])/(a[2] * a[4] - a[1] * a[5])
  //where alp is a coefficient of y[k-1] and bet is coefficient of u[k]
  return alp, bet
}

func main(){
  u := []float64{0, 2, 1, 2, 0, 1}
  y := []float64{0, 1, 1.5, 2.5, 2.5, 3.0}
  y_1 := make([]float64, 6)
  y_1[0] = 0
  
  var alp, bet float64
  alp, bet = lsm(y, u)
  fmt.Printf("alp = %f\n", alp)
  fmt.Printf("bet = %f\n", bet)

  var _alp, _bet float64
  var q = 0.99
  _alp, _bet = rls(q, y, u)
  fmt.Printf("_alp = %f\n", _alp)
  fmt.Printf("_bet = %f\n", _bet)

  return
}