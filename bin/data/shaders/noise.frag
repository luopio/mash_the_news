#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex0;

void main(){
	vec3 val = vec3( texture2DRect(tex0, gl_FragCoord.xy) );

	if(val[0] != 0.0) {
        // gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);
        gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0); //cell lives...
    } else {
        gl_FragColor = gl_Color;
    }

}
