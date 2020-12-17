int average(int count, int (*func) ()) {
  int sum = 0;
  for(int i = 0; i < count; i++) {
    sum += func();
  }
  return sum / count;
}
