/* Empty function to fill 0x00 */
void entrypoint() {}

void main() {
  char *video_memory = (char *)0xb8000;
  *video_memory = 'D';
}
