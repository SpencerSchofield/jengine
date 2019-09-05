#version 450 core

//in vec4 vertColor;

out vec4 color;

uniform vec2 size;
uniform vec4 offset;

void main() {
    vec4 co_ord;
    co_ord.x = (gl_FragCoord.x/size.x)*(offset.y-offset.x)+offset.x;
    co_ord.y = (gl_FragCoord.y/size.y)*(offset.w-offset.z)+offset.z;
    float x = 0;
    float y = 0;
    int it = 0;
    int mit = 10000;
    while (x*x + y*y < 4 && it < mit) {
	float xx = x*x - y*y + co_ord.x;
	y = 2*x*y+co_ord.y;
	x = xx;
	it++;
    }

    if (it != mit) {
	float hue = 6 * it / float(mit);
	int i = int(hue);
	float ff = hue - i;
	float q = 1.0 - ff;
	vec4 a[] = {
	    vec4(1,ff,0,1),
	    vec4(q,1,0,1),
	    vec4(0,1,ff,1),
	    vec4(0,q,1,1),
	    vec4(ff,0,1,1),
	    vec4(1,0,q,1)
	};
	color = a[i];
    }
    else {
	color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
}


