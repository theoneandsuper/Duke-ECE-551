unsigned power(unsigned x, unsigned y) {
	if (y == 0) {
		return 1u;
	}
	if (x == 0) {
		return 0u;
	}
	return x * power(x, y - 1);
}	
