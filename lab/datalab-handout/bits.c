
/*ALUNO:JEFSON ALVES MATOS - MATRICULA:201511651
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

   /* Vai adicionar bits dividindo os 32 bits pela metade repetidamente
 Usando máscaras e adicionando até que toda adição se torne "vertical" */

	/* Primeiro precisa declarar nossas máscaras */
	unsigned mask1 = 0x55;
	unsigned mask2 = 0x33;
	unsigned mask3 = 0x0F;


	mask1 = (mask1 << 8) + 0x55;
	mask1 = (mask1 << 8) + 0x55;
	mask1 = (mask1 << 8) + 0x55; /* mudamos 3x então é agora 0x55555555 */
	/*mask1 = 010101...*/

	mask2 = (mask2 << 8) + 0x33;
        mask2 = (mask2 << 8) + 0x33;
        mask2 = (mask2 << 8) + 0x33;
	/*mask2 = 00110011...*/

	mask3 = (mask3 << 8) + 0x0F;
        mask3 = (mask3 << 8) + 0x0F;
        mask3 = (mask3 << 8) + 0x0F;
	/*mask3 = 00001111...*/

	x = x + (~((x>>1) & mask1) + 1); /*primeiro split*/
	x = (x & mask2) + ((x >>2) & mask2); /*split 2*/
	x = (x & mask3) + ((x >>4) & mask3); /*split 3*/
	/*Apenas adicionar os bits até que eles sejam "empilhados" inteiramente */

	x = x + (x>>8);
	x = x + (x>>16);

	/* A resposta tem um tamanho máximo de 32, então e com os últimos 6 bits */
	return (x & 0x3F /*00...111111*/);
}
/*
 * bang - Compute !x withresul using !
 *   Examples: badepng(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
 int bang(int x) {
 	int sinalx = (x >> 31); /*0 ou 1 dependendo do sinal */
 	int girasinalX = (((~x) + 1) >> 31); /* Isso deve ser 1 ou 0 */

  /* A única vez que sinalx e girasinalX são ambos 0 é se x foi originalmente
  0. Isso ocorre porque adicionar 1 a ~ 0 == 0 */
 	return ((~(sinalx | girasinalX)) & 1);
 }
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
 int tmin(void)
 {
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
 int divpwr2(int x, int n)
 {
   /* Tudo o que precisa ser feito aqui é uma mudança aritmética direita por n bits. Contudo,
   1 precisa ser adicionado ao x depois que ele é deslocado em determinadas situações.
	 */
	 int aux = (x >> 31) & (~!((~(x & (~x + 1)) + (1 << n)) >> 31) + 1);
   x = x >> n;
   return (~aux & x) | (aux & (x + 1));
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
   /* Use 1<<31 to mask sign bit. Use !x to test for x=0. XOR to combine them. */
   int resul = !((1 << 31) & x);
   int iszero = !x;
   return resul ^ iszero;
 }
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
 int isLessOrEqual(int x, int y)
 {
    int negX = ~x+1;
    int addY = negX + y; /*negative se x > y*/
    int verificaSinal = addY >> 31 & 1;
    /* O acima não funcionará para valores que empurram os limites de ints
       O código a seguir verifica valores muito grandes / pequenos */
    int BitEsq = 1 << 31;
    int xEsq = BitEsq & x;
    int yEsq = BitEsq & y;
    int Ordx = xEsq ^ yEsq;
    Ordx = (Ordx >> 31) & 1;

    return (Ordx & (xEsq>>31)) | (!verificaSinal & !Ordx);
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
 unsigned float_neg(unsigned uf)
 {
    int verificaNaN = 0x000000FF << 23; /* 1's nos 8 bits de expoente */
    int frac = 0x7FFFFF & uf; /*Contém apenas o valor da fração*/

    /*retorna o argumento se os bits do estado são todos os 1 e frac não é zero*/
    if((verificaNaN & uf) == verificaNaN && frac)
       return uf;

    /*Caso contrário, basta virar o bit de sinal*/
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
 /*1) quando x = 0, retornar 0;
  2) então faça x positivo;
  3) próximo encontrar log2 (2);
  4) adicionar expoente;
  5) adicionar fração;
  6) rodada;
  7) retornar x_novo;*/
 	unsigned i, a, y, novo_x, b, c, d;
 	d = 1;
 	if (x){
 		d = 0;
 	}
 	if (d){
 		return x;
 	}
 	c = 0x80000000;
 	novo_x = c & x;
 	if (novo_x){		   // Faça x positivo
 		x = -x;
 	}
 	a = x;
 	i = 126;			// Encontra log2(x)
 	while (a){
 		a >>= 1;
 		i += 1;
 	};

 	novo_x += (i << 23);
 	x <<= (157 - i);
 	y = x >> 7;
 	b = 0x007FFFFF;
 	y &= b;
 	novo_x += y;			// fração
 	novo_x += (0x40 & x) && (0x40 ^ (x & 0xff));  			// rodada
 	return novo_x;

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
 	//uf = +-0 caso.
 	if(uf==0 || uf == 0x80000000) return uf;
 	//NaN caso.
 	if(((uf>>23) & 0xff) == 0xff) return uf;
 	//Valor minúsculo, mas caso não-zero.
 	if(((uf>>23) & 0xff) == 0x00) {
 		return (uf & (1<<31)) | (uf<<1);
 	}
 	//Caso contrário, adicione 1 ao valor exp.
 	return uf + (1<<23);
 }
