uniform float opacity;
varying vec4 vColor;
void main(void) {
    gl_FragColor = vec4(vColor.rgb, vColor.a * opacity);
}