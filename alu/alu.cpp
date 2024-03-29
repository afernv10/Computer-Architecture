#include "alu.h"
#include <iostream>
#include <math.h>
//#define STEP_trazas
//#define STEP_13

using namespace std;

alu::alu()
{

}

void alu::setValoresA(unsigned int s, unsigned int e, unsigned int f){
    this->sa = s;
    this->ea = e;
    this->fa = f;
}

void alu::setValoresB(unsigned int s, unsigned int e, unsigned int f){
    this->sb = s;
    this->eb = e;
    this->fb = f;
}

void alu::setValoresEnteros(unsigned int valorEnteroA, unsigned int valorEnteroB){
    this->aEntero = valorEnteroA;
    this->bEntero = valorEnteroB;
}

unsigned int alu::getSignoResultado(){
    return this->resultadoS;
}

unsigned int alu::getExponenteResultado(){
    return this->resultadoE;
}

unsigned int alu::getFraccionariaResultado(){
    return this->resultadoF;
}

/**
 * EN REALIDAD LA MANTISA FUERA DE LA CLASE ALU NO VALE PA NA, o sea que este metodo no lo uso de momento
 * @brief alu::getMantisaResultado
 * @return
 */
unsigned int alu::getMantisaResultado(){
    return this->resultadoM;
}

bool alu::esDenormal(unsigned int s, unsigned int e, unsigned int f){

    if(e == 0x00000000){
        return true;
    }
    return false;
}

bool alu::esInfinito(unsigned int s, unsigned int e, unsigned int f){
    if(e == +0 && f == 0x00000000){
        return true;
    }
    return false;
}

bool alu::esNaN(unsigned int s, unsigned int e, unsigned int f){
    if(e == 255 && f != 0x00000000){
        return true;
    }
    return false;
}

bool alu::checkResultadoIndeterminado(){
    return resultadoIndeterminadoNaN;
}

bool alu::checkResultadoInfinito(){
    return resultadoInfinito;
}

bool alu::checkResultadoUnderflow(){
    return resultadoUnderflow;
}

bool alu::checkResultadoNaN(){
    return resultadoNaN;
}

void alu::suma(){
    // los valores que tenemos en alu son:
#ifdef STEP_trazas
    std::cout << "a: " << sa << " " << ea << " " << fa << endl;
    std::cout << "b: " << sb << " " << eb << " " << fb << endl;
    std::cout << "***************************************" << endl;
#endif

    unsigned int P = 0x00000000;
    unsigned int ma, mb = 0;
    unsigned int g, r, st = 0x00000000;
    unsigned int ss, es, fs, ms = 0;
    bool operandos_intercambiados = false;
    bool compl_P = false;
    int ea_valor, eb_valor = 0x00000000;
    unsigned int parte_entera_a, parte_entera_b;

    if(esDenormal(sa, ea, fa)){
        ea_valor = -126;
        ea = 1;
        parte_entera_a = 0;
        ma = (parte_entera_a<<23)|fa;
    } else if(esInfinito(sa, ea, fa)){

    } else if(esNaN(sa, ea, fa)){
        sa = 0;
    } else {
        ea_valor = ea-127;
        parte_entera_a = 1;
        ma = (parte_entera_a<<23)|fa;
    }
    if(esDenormal(sb, eb, fb)){
        eb_valor = -126;
        eb = 1;
        parte_entera_b = 0;
        mb = (parte_entera_b<<23)|fb;
    } else if(esInfinito(sb, eb, fb)){

    } else if(esNaN(sb, eb, fb)){

    } else {
        eb_valor = eb-127;
        parte_entera_b = 1;
        mb = (parte_entera_b<<23)|fb;
    }

    if(ea<eb){
        // intercambiamos operandos
        unsigned int auxs = sa;
        unsigned int auxe = ea;
        unsigned int auxf = fa;
        unsigned int auxm = ma;
        sa = sb;
        ea = eb;
        fa = fb;
        ma = mb;
        sb = auxs;
        eb = auxe;
        fb = auxf;
        mb = auxm;
        operandos_intercambiados = true;
    }


    /****************************************************************************
     *                         PASO 3. Asignar
     ****************************************************************************/
    es = ea;
    unsigned int d = ea-eb;


    /****************************************************************************
     *                      PASO 4. comprobar s
     ****************************************************************************/
    if(sa!=sb){
        mb = ~mb;
        mb = mb + 1;

    }

    /****************************** PASO 5 ***************************************
     * quitamos los numeros que queden por la izq del 24 bit, generados con el C2
     * para mantener lo que tenemos hacemos AND con 000000...1111111
     * ***************************************************************************/
    mb = mb & 0x00ffffff;
    P = mb;


    /****************************************************************************
     *                              PASO 6
     * Asignar bit de guarda, de redondeo y sticky siempre que existan
     *
     ****************************************************************************/

    g = ((1<<(d-1))&P)>>(d-1);

    int i;
    if(d>=2){
        r = ((1<<(d-2))&P)>>(d-2);

        for(i = 0; i<d-2; i++){
            if((P&(1<<i)) == 0x00000001){
                st = 1;
                break;
            }
        }
    }


    /*****************************************
     *                  PASO 7
     *****************************************/
    if(sa!=sb){
        // desplazar P a la dcha d bits introduciendo 1 por la izquierda
        for(i = 0; i<d; i++){
            P = (P>>1)|(1<<23);
        }


    } else {
        // desplazar P a la dcha d bits introduciendo 0 por la izqda
        for(i = 0; i<d; i++){
            P = (P>>1)&(0xff7fffff);
        }

    }

    /**************************************************************
     *                  PASO 8
     *          8 suma y obtenemos acarreo
     **************************************************************/
    P = ma + P;
    unsigned int c1;
    unsigned int bit25 = P & 0x01000000;
    c1 = bit25>>24;
    // quitamos el bit de acarreo a P
    P = P & 0x00ffffff;


    /*********************************************************
     *                      PASO 9
     * *******************************************************/
    if((sa != sb) && ((P&0x00800000) == 0x00800000) && (c1==0)){    //...&& Pn-1==1 && ...
        P = ~P + 1;
        P = P & 0x00ffffff; // no se si hay que contar el acarreo o no (24 o 25 bits) aquí no lo considero
        compl_P = true;
    }

    /**********************************************************
     *                      PASO 10
     **********************************************************/
    if((sa==sb) && (c1==1)){
        st = g | r | st;
        r = P & 0x00000001 ;   // P(0)
        P = ((c1<<24)|P)>>1;    // añadimos el c1 y desplazamos a dcha 1 bit
        es = es + 1;

    } else {

        int k = 0;
        unsigned int auxP = P;

        if(auxP != 0){
            while(((1<<23)&auxP) != 0x00800000){
                auxP = auxP<<1;
                k++;
            }

            if(k==0){
                st = r|st;
                r = g;
            } else if(k>1){
                r = 0;
                st = 0;
            }

            if(g==0){
                P = (P<<k);
            } else {
                int n = 0;
                for(i = 0; i<k; i++){
                    P = (P<<(n+1))|g;
                }
            }

                // quitamos lo sobrante a partir del 24 bit
            P = P & 0x00ffffff;
            es = es-k;

        } else {
            es = 0;
        }
    }


    /**************************************************
     *                     PASO 11
     *                  redondear a P
     **************************************************/
    unsigned int c2 = 0;
    unsigned int parac2 = 0;
    // Pcero = P & 0x00000001;

    if((r == 1 && st == 1) || (r==1 && st==0 && ((P & 0x00000001) == 0x00000001))){
          P = P + 1;

            /*
             * operacion AND para quedarnos con lo que hay en el bit 25,
             * para comprobar si hay acarreo, si hay 1 sería = 0x01000000
             * */
          parac2 = P & 0x01000000;
          if(parac2 == 0x01000000){
              c2 = 1;
              P = (P<<1);   // aqui está incluido el c2
              es = es+1;
          } else {
              c2 = 0;
          }
    }
    ms = P;


    /*******************************************************
     *                    PASO 12
     *              signo del resultado
     *******************************************************/

    if(!operandos_intercambiados && compl_P){
        ss = sb;
    } else {
        ss = sa;
    }

    /******************************************************
     *                      PASO 13
     ******************************************************/
    int signoResult = 0;
    if(ss==0){
       signoResult = 1;
    } else {
        signoResult = -1;
    }

    fs = (ms&0x007fffff);
    this->resultadoS = ss;
    this->resultadoE = es;
    this->resultadoM = ms;
    this->resultadoF = fs;
#ifdef STEP_13
    std::cout << "STEP 13" << endl;
    std::cout << "  sa " << sa;
    std::cout << "  ea " << ea;
    std::cout << "  ma " << ma << endl;
    std::cout << "  sb " << sb;
    std::cout << "  eb " << eb;
    std::cout << "  mb " << mb << endl;

    std::cout << "  SUMA ss*ms*2^es " << endl;
    std::cout << "  ss " << ss;
    std::cout << "  es " << es;
    std::cout << "  ms " << ms;
    std::cout << "  fs " << fs;
    std::cout << "  resultado =  " << (float)signoResult*(float)ms*(float)pow(2,es-127) << endl;
    std::cout << "***************************************" << endl;
#endif
}

void alu::multiplicacionBinariaSinSigno(unsigned int x, unsigned int y){

    unsigned int P = 0;
    unsigned int c = 0;

    int i;
    for(i = 0; i < 24; i++){
        if(((x & 0x00000001) == 0x00000001)){
            P = P + y;
            c = (P & 0x01000000)>>24;   // obtenemos el acarreo
            P = P & 0x00ffffff;         // quitamos lo sobrante por la izquierda

        } else {
            P = P + 0;
            P = P & 0x00ffffff;
        }
        // desplazar 1 bit a dcha
        unsigned int bit0_P = P & 0x00000001;
        x = (x>>1) | (bit0_P<<23);
        P = (P>>1) | (c<<23);
        c = c>>1;
        //PA = ((c<<48) | (P<<24) | (x))>>1;
    }

    this->mbs_c = c;
    this->mbs_P = P;
    this->mbs_A = x;
}

void alu::producto(){


    unsigned int ma, mb, parte_entera_a, parte_entera_b;
    int ea_valor, eb_valor;
    unsigned int sp, ep, fp, mp;
    unsigned int r, st;
    unsigned int P, A;

    // reiniciamos a false
    resultadoIndeterminadoNaN = false;
    resultadoInfinito = false;
    resultadoUnderflow = false;
    resultadoNaN = false;


    // Comprobación operandos cero
    if(aEntero == 0 || bEntero == 0){
        if(esInfinito(sa, ea, fa) || esInfinito(sb, eb, fb)){
            resultadoIndeterminadoNaN = true;
        } else {
            this->resultadoS = 0;
            this->resultadoE = 0;
            this->resultadoM = 0;
            this->resultadoF = 0;
        }
        return;
    }
    /************************************************************/
    if(esDenormal(sa, ea, fa)){
        ea_valor = -126;
        ea = 1;
        parte_entera_a = 0;
        ma = (parte_entera_a<<23)|fa;
        resultadoNaN = true;
        return;
    } else if(esInfinito(sa, ea, fa)){

    } else if(esNaN(sa, ea, fa)){
        sa = 0;
    } else {
        ea_valor = ea-127;
        parte_entera_a = 1;
        ma = (parte_entera_a<<23)|fa;
    }
    if(esDenormal(sb, eb, fb)){
        eb_valor = -126;
        eb = 1;
        parte_entera_b = 0;
        mb = (parte_entera_b<<23)|fb;
        resultadoNaN = true;
        return;
    } else if(esInfinito(sb, eb, fb)){

    } else if(esNaN(sb, eb, fb)){

    } else {
        eb_valor = eb-127;
        parte_entera_b = 1;
        mb = (parte_entera_b<<23)|fb;
    }
    /***************************************************************/

    // 1. signo del producto = sa*sb
    int signoA = 1;
    int signoB = 1;
    if(sa!=0){
        signoA = -1;
    }
    if(sb!=0){
        signoB = -1;
    }
    int signofinal = signoA*signoB;
    if(signofinal==-1){
        sp = 1;
    } else {
        sp = 0;
    }
    //sp = sa*sb;

    // 2. exponente del producto = ea+eb
    //ep = ea_valor + eb_valor;
    ep = ea + eb;
    int ep2 = ea_valor+eb_valor;

    // 3. calculo de mp

        // i. (P,A)=ma*mb con alg enteros si signo
        multiplicacionBinariaSinSigno(ma, mb);
        P = mbs_P;
        A = mbs_A;

        // si p(n-1)= 0 desplazar (P,A) <<1
        if(((1<<23)&P) == 0x00000000 ){
            unsigned int ultBit = ((1<<23)&A)>>23;
            P = (P<<1)|ultBit;                       // OJO
            A = A<<1;
        } else{
            ep = ep+1;
        }

        // iv. bit redondeo y st
        r = ((1<<23)&A)>>(23);   // cogemos el bit 24 de A, desplazamos hasta el 0 para ponerlo en forma de 1 bit

        int i;
        st = 0;
        for(i = 0; i<24-2; i++){
            if(((A&(1<<i))>>i) == 0x00000001){
                st = 1;
                break;
            }
        }


        // v. Redondeo
        if(((r == 1) && (st == 1)) || ((r == 1) && (st == 0) && ((P & 0x00000001) == 0x00000001))){
            P = P + 1;
        }
            // desbordamientos
       // unsigned int EXPMAX = 4294967295;  //4294967295 = todo unos = 0xFFFFFFFF // 0x000000ff
        unsigned int EXPMAX = 255;
        int EXPMIN = 0;

        unsigned int t;
        ep2 = ep-127;
            // 1. desbord a infinito
        if(ep-127 > EXPMAX && ep2 > 0){
            //overflow
            resultadoInfinito = true;
            return;
        } else if(ep2 < EXPMIN){
            t = EXPMIN - (ep2+127);
            if(t >= 24){
                // underflow
                resultadoUnderflow = true;
                return;
            } else {
                //PA = PA>>t; // resultado sera denormal       // este despl como es???????????
                for(i = 0; i<t; i++){
                    unsigned int bit0_P = P & 0x00000001;
                    A = (A>>1) | (bit0_P<<23);
                    P = (P>>1);
                }

                ep = EXPMIN;
            }
        }

            // tratamiento denormales
        unsigned int t1, t2;
        // 1
        if(esDenormal(sa, ea, fa) || esDenormal(sb, eb, fb)){
            if(ep < EXPMIN){
                // lo mismo que underflow
                t = EXPMIN - ep;
                if(t >= 24){
                    // underflow
                    resultadoUnderflow = true;
                } else {
                    //PA = PA>>t; // resultado sera denormal          // este despl como es???????????
                    for(i = 0; i<t; i++){
                        unsigned int bit0_P = P & 0x00000001;
                        A = (A>>1) | (bit0_P<<23);
                        P = (P>>1);
                    }
                    ep = EXPMIN;
                }
            } else if(ep > EXPMIN){
                t1 = ep-EXPMIN;
                // cuanto hay que desplazar PA a la izq para que quede normalizada
                int k = 0;
                unsigned int auxP = P;

                while(((1<<23)&auxP) != 0x00800000){
                    auxP = auxP<<1;
                    k++;
                }
                t2 = k;//n bits necesarios para desplazr PA a izq para que quede normalizada

                if(t1<t2){
                    t = t1;
                } else {
                     t = t2;
                     // si son iguales ??????????
                }

                ep = ep-t;
                //PA = PA<<t;     // este despl como es???????????
                for(i = 0; i<t; i++){
                    unsigned int bit23_A = (A & 0x00800000)>>23;
                    P = (P<<1) | (bit23_A);
                    A = A<<1;
                    P = P & 0x00ffffff;
                    A = A & 0x00ffffff;
                }
            } else {    // ep == EXPMIN
                // reultado denormal
                resultadoNaN = true;
            }
        }

        // tratamiento de cero

        mp = P;
        fp = (mp&0x007fffff);
        // resultado
        this->resultadoS = sp;
        this->resultadoE = ep-127;
        this->resultadoM = mp;
        this->resultadoF = fp;

#ifdef STEP_trazas
        std::cout << "  PRODUCTO " << endl;
        std::cout << "  sp " << sp;
        std::cout << "  ep " << ep;
        std::cout << "  mp " << mp;
        std::cout << "  fp " << fp << endl;
#endif
}

unsigned int alu::multiplica(unsigned int a, unsigned int b){

    unsigned int auxEnteroA = aEntero;
    unsigned int auxSa = sa;
    unsigned int auxEa = ea;
    unsigned int auxFa = fa;

    unsigned int auxEnteroB = bEntero;
    unsigned int auxSb = sb;
    unsigned int auxEb = eb;
    unsigned int auxFb = fb;

    union unionDato ap_union;
    ap_union.valorEntero = a;
    aEntero = a;
    sa = ap_union.campos.signo;
    ea = ap_union.campos.exponente;
    fa = ap_union.campos.frac;

    union unionDato bp_union;
    bp_union.valorEntero = b;
    bEntero = b;
    sb = bp_union.campos.signo;
    eb = bp_union.campos.exponente;
    fb = bp_union.campos.frac;

    producto();

    union unionDato resultado;
    resultado.campos.signo = this->resultadoS;
    resultado.campos.exponente = this->resultadoE;
    resultado.campos.frac = this->resultadoF;

    aEntero = auxEnteroA;
    sa = auxSa;
    ea = auxEa;
    fa = auxFa;

    bEntero = auxEnteroB;
    sb = auxSb;
    eb = auxEb;
    fb = auxFb;


    return resultado.valorEntero;
}

unsigned int alu::sumaDiv(unsigned int a, unsigned int b){

    union unionDato ap_union;
    ap_union.valorEntero = a;
    aEntero = a;
    sa = ap_union.campos.signo;
    ea = ap_union.campos.exponente;
    fa = ap_union.campos.frac;

    union unionDato bp_union;
    bp_union.valorEntero = b;
    bEntero = b;
    sb = bp_union.campos.signo;
    if(bp_union.campos.signo==1){
        bp_union.campos.signo = 0;
    } else {
        bp_union.campos.signo = 1;
    }
    bEntero = bp_union.valorEntero;
    sb = bp_union.campos.signo;
    eb = bp_union.campos.exponente;
    fb = bp_union.campos.frac;

    suma();

    union unionDato resultado;
    resultado.campos.signo = this->resultadoS;
    resultado.campos.exponente = this->resultadoE;
    resultado.campos.frac = this->resultadoF;

    if(sb==1){
        sb = 0;
    } else {
        sb = 1;
    }

    return resultado.valorEntero;
}

void alu::division(){

    unsigned int ma, mb, parte_entera_a, parte_entera_b, ea_valor, eb_valor;

    /************************************************************/
    if(esDenormal(sa, ea, fa)){
        ea_valor = -126;
        ea = 1;
        parte_entera_a = 0;
        ma = (parte_entera_a<<23)|fa;
    } else if(esInfinito(sa, ea, fa)){

    } else if(esNaN(sa, ea, fa)){
        sa = 0;
    } else {
        ea_valor = ea-127;
        parte_entera_a = 1;
        ma = (parte_entera_a<<23)|fa;
    }
    if(esDenormal(sb, eb, fb)){
        eb_valor = -126;
        eb = 1;
        parte_entera_b = 0;
        mb = (parte_entera_b<<23)|fb;
    } else if(esInfinito(sb, eb, fb)){

    } else if(esNaN(sb, eb, fb)){

    } else {
        eb_valor = eb-127;
        parte_entera_b = 1;
        mb = (parte_entera_b<<23)|fb;
    }
    /***************************************************************/

    /* Equivalencias mantisa float y unsigned:
     * mantisa [1, 2)
     * mantisa [0x00000001, 0x00ffffff)
    */
    /**********************************************/
    /* PASO 1. Escalar                            */
    /**********************************************/

    while(eb!=127){

        if(eb<127){
            eb = eb+1;
            ea = ea+1;
        } else if(eb>127){
            eb = eb-1;
            ea = ea-1;
        }
    }
    unsigned int signoInicioA = 0, signoInicioB = 0;
    if(sa==1 || sb==1){
        signoInicioA = sa;
        signoInicioB = sb;
        sa = 0;
        sb = 0;
    }

    aEntero = ponerEnIEEE754(sa, ea, fa);
    bEntero = ponerEnIEEE754(sb, eb, fb);

    /**********************************************
     * PASO 2. Buscar b' con valores de la tabla
     * [1, 1.25) ----> 1
     * [1.25, 2) ----> 0.8
     *
     * en unsigned/hex
     * [0x00000001, 0x00a00000) ----> 1 ----float-> 0x3f800000
     * [0x00a00000, 0x00ffffff) ----> 0.8 --float-> 0x3f4ccccd , en unsigned int es 1061997773
     * *******************************************/
    unsigned int bprima;
    if(bEntero>=0x3f800000 && bEntero<0x3fa00000){
        bprima = 0x3f800000;
    } else {
        bprima = 0x3f4ccccd;
    }

    /**********************************************
     * PASO 3. Asignar
     *
     * x = a * bprima;
     * y = b * bprima;
     * *******************************************/

    unsigned int x = multiplica(aEntero, bprima);
    unsigned int y = multiplica(bEntero, bprima);   // el error aqui

    /**********************************************
     * PASO 4. Iterar
     * *******************************************/
    unsigned int r;

    while(1){
        // r = 2 - y // 2 = 0x40000000
        r = sumaDiv(0x40000000, y);
        unsigned int prevY = y;
        y = multiplica(prevY, r);
        unsigned int prevX = x;
        x = multiplica(prevX, r);

        unsigned int solu = sumaDiv(x, prevX);
        union unionDato abs;
        abs.valorEntero = solu;
        abs.campos.signo = 0;
        if(abs.valorEntero < 0x3a83126f){
            break;
        }
    }

    union unionDato resultado;
    resultado.valorEntero = x;
    if(signoInicioA != signoInicioB ){
        resultado.campos.signo = 1;
    }
    this->resultadoS = resultado.campos.signo ;
    this->resultadoE = resultado.campos.exponente;
    this->resultadoF = resultado.campos.frac;

}

unsigned int alu::ponerEnIEEE754(unsigned int signo, unsigned int exponente, unsigned int fraccionaria){

    struct ieee754{
        unsigned int f:23;
        unsigned int e:8;
        unsigned int s:1;
    };

    union num{
        struct ieee754 parts;
        unsigned int valorEntero;
    };

    union num n;

    n.parts.s = signo;
    n.parts.e = exponente;
    n.parts.f = fraccionaria;

    return n.valorEntero;

}

void alu::asignarValoresClaseIEEE(int n, unsigned int signo, unsigned int exponente, unsigned int fraccionaria){
    if(n==1){
        sa = signo;
        ea = exponente;
        fa = fraccionaria;
    } else {
        sb = signo;
        sb = exponente;
        fb = fraccionaria;
    }
}
