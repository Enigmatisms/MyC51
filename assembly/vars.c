int _a, _b, _c, _d;
int x, y, z;
int c[8];
int f[8];

void setup(){
		int i;
		_a = 0;
		_b = 0;
		y = 8;
		for (i = 0; i < y; i++){
				c[i] = i + 1;
				f[i] = i + 1;
		}
		for (i = 0; i < y; i++){
				_b = _b + c[i] * f[i];
		}
		_c = 0;
		_d = 0;
		x = 0;
		z = 0;
}

void loop(){
		while(1);
}