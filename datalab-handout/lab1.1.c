
/*ALUNO:JEFSON ALVES MATOS - MATRICULA:201511651 */

/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
	//Lei de morgan
	return ~(~x |~y);
}

/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
 int getByte(int x, int n) {
	//Tranforma o valor de n em byte (x8), desloca x n vezes para os ultimos bits e extrai apenas o ltimo byte, que é o byte da posisao n
	return (x >> (n << 3)) & 0xFF;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
 int logicalShift(int x, int n) {
	//Realiza deslocamento e zero os 1s que aparecem no final quando aparecer
    return (x >> n) & ~((((0x1) << 31) >> n) << 1);
 }
 
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
 int bitCount(int x) {
	int m1=0x11 | (0x11<<8);
	int mask=m1 | (m1<<16);
	int s = x&mask;
	s+=x>>1&mask;
	s+=x>>2&mask;
	s+=x>>3&mask;
	s=s+(s>>16);
	mask=0xf | (0xf<<8);
	s=(s&mask)+((s>>4)&mask);
	return (s+(s>>8))&0x3f;
}

/*
 * bang - Compute !x without using !
 *   Examples: badepng(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x) {
	int signX = (x >> 31); /*0 ou 1 dependendo do sinal */
	int flipSignX = (((~x) + 1) >> 31); /* Isso deve ser 1 ou 0 */

	/* A única vez que signX e flipSignX são ambos 0 é se x foi originalmente 0. Isso ocorre porque adicionar 1 a ~ 0 == 0 */
	return ((~(signX | flipSignX)) & 1);
}

/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	return  1 << 31; /* Muda o bit '1' para obter 0x80000000*/
}

/*
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
	/* Mascara o bit de sinal ~ x e vice-versa para obter o bit mais alto em x. Muda por n-1, e não. */
	int mask = x >> 31;
	return !(((~x & mask) + (x & ~mask)) >> (n + ~0));
}

/*
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
	// Tudo o que precisa ser feito aqui é uma mudança aritmética direita por n bits. Contudo,
	// 1 precisa ser adicionado ao x depois que ele é deslocado em determinadas situações.
	int shouldFix = (x >> 31) & (~!((~(x & (~x + 1)) + (1 << n)) >> 31) + 1);
	x = x >> n;
	return (~shouldFix & x) | (shouldFix & (x + 1));
}
 
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	return ~x + 1;
}

/*
 * isPositive - return 1 if x > 0, return 0 otherwise
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
	/* Use 1<<31 para saber o sinal. Use !x para saber se x é diferente de zero. */
	int out = !((1 << 31) & x);
	int iszero = !x;
	return out ^ iszero;
}

/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	int negX = ~x+1;
	int addY = negX + y; /*negativo quando x > y*/
	int checkSign = addY >> 31 & 1;
	/*the above will not work for values that push the bounds of ints the following code checks very large/small values*/
	int leftBit = 1 << 31;
	int xLeft = leftBit & x;
	int yLeft = leftBit & y;
	int xOrd = xLeft ^ yLeft;
	xOrd = (xOrd >> 31) & 1;
	return (xOrd & (xLeft>>31)) | (!checkSign & !xOrd);
}

/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
	/* Olho pra metade do numero e verifico se la tem 1, se tiver realizo o procedimento para metade da metade e assim por diante */
	/* Quando tem olho pra metade superior, quando não olho para a metade anterior */
	
	int a16, a8, a4, a2, a1, b16, b8, b4, b2;
	a16 = !(!(x >> 16));
	b16 = a16 << 4;
	a8 = !(!(x >> (8 + b16)));
	b8 = (a8 << 3) + b16;
	a4 = !(!(x >> (4 + b8)));
	b4 = (a4 << 2) + b8;
	a2 = !(!(x >> (2 + b4)));
	b2 = (a2 << 1) + b4;
	a1 = (x >> (1 + b2));
	return a1 + b2;
}

/*
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
	int nanCheck = 0x000000FF << 23; /*1's in the 8 exponent bits*/
	int frac = 0x7FFFFF & uf; /*contains just the fraction value*/

	/*return argument if exp bits are all 1's and frac is not zero*/
	if((nanCheck & uf) == nanCheck && frac)
	return uf;

	/*otherwise, just flip the sign bit*/
	return uf ^ (1 << 31);
}
 
/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
 unsigned float_i2f(int x) {
 /*      1) when x = 0, return 0;
 	2) then make x positive;
 	3) next find log2(2);
 	4) add exponent;
 	5) add fraction;
 	6) round;
 	7) return x_new;  			*/
 	unsigned i, a, y, x_new, b, c, d;
 	d = 1;
 	if (x){
 		d = 0;
 	}
 	if (d){
 		return x;
 	}
 	c = 0x80000000;
 	x_new = c & x;
 	if (x_new){		   // make x positive
 		x = -x;
 	}
 	a = x;
 	i = 126;			// find log2(x)
 	while (a){
 		a >>= 1;
 		i += 1;
 	};

 	x_new += (i << 23);
 	x <<= (157 - i);
 	y = x >> 7;
 	b = 0x007FFFFF;
 	y &= b;
 	x_new += y;			// fraction
 	x_new += (0x40 & x) && (0x40 ^ (x & 0xff));  			// round
 	return x_new;

}
/*
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
 unsigned float_twice(unsigned uf) {
 	//uf = +-0 case.
 	if(uf==0 || uf == 0x80000000) return uf;
 	//NaN case.
 	if(((uf>>23) & 0xff) == 0xff) return uf;
 	//Tiny value, but non-zero case.
 	if(((uf>>23) & 0xff) == 0x00) {
 		return (uf & (1<<31)) | (uf<<1);
 	}
 	//Otherwise, Add 1 to exp value.
 	return uf + (1<<23);
 }
