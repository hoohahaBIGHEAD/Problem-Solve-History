typedef enum _boolean {
	FALSE,
	TRUE
} boolean;

#define FALSE 0
#define TRUE 1

int main(int argc, char* argv[]) {


	return 0;
}

boolean isPrime(int x) {

	int i;
	if (x <= 1) return FALSE;
	for ( i = 2; i < x; i++)
		if (((x % i) == 0) && (i != x)) return FALSE;
	return TRUE;
}