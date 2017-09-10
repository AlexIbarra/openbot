#ifndef MODULOMOTOR_H
#define MODULOMOTOR_H

/*! \brief Funcion que inicializa el modulo de motores
 * 
 *  Permite inicializar los parametros principales para el funcnionamiento
 *  de los motores.
 */
void initMotores();

/*! \brief Funcion para detener los motores
 * 
 *  Manda las señales PWM correctas para conseguir detener los motores.
 */
void parar();

/*! \brief Funcion que las ruedas giren en sentido contrario
 * 
 *  Manda las señales PWM que permiten que los motores giren en sentido contrario
 *  para que el robot pueda retroceder.
 */
void retroceder();

/*! 
 * \brief Funcion para hacer girar los motores hacia adelante
 * 
 *  Permite hacer girar ambos motores a la misma velocidad para conseguir que
 *  siga una trayectoria recta hasta el objetivo.
 */
void avanza();

/*! 
 * \brief Funcion para hacer girar los motores hacia adelante
 * 
 *  Al igual que la funcion "avanza", esta permite hacer girar ambos motores
 *  en direccion recta hasta el objetivo pero a una velocidad menor.
 */
void avanzaLento();

/*! 
 * \brief Funcion para rotar hacia la izquierda
 * 
 *  Permite hacer que los motores giren en direccion izquierda.
 */
void rotaIzq();

/*! 
 * \brief Funcion para rotar hacia la derecha
 * 
 *  Permite que los motores giren en direccion derecha.
 */
void rotaDcha();

/*! 
 * \brief Funcion para girar levemente hacia la izquierda
 * 
 */
void trayectoriaIzq();

/*! 
 * \brief Funcion para girar levemente hacia la derecha
 * 
 */
void trayectoriaDer();

/*! 
 * \brief Hace dar al robot una vuelta completa hacia la derecha
 * 
 */
void vuelta();

/*! 
 * \brief Hace un barrido de unos 60 grados aproximadamente
 * 
 */
void giraFoto();

/*! 
 * \brief El robot da una vuelta más rápida a la derecha
 * 
 */
void vueltaRapida();

#endif /* MODULOMOTOR_H */
