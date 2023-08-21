int _printf(const char *format, ...) {
  va_list list;
  char buffer[BUFF_SIZE];
  int i = 0;
  int (*print_fn)(va_list, char[], int, int, int, int);

  va_start(list, format);

  while (format[i]) {
    if (format[i] == '%') {
      i++;
      print_fn = get_print_fn(format[i]);
      print_fn(list, buffer, i, width, precision, size);
      i++;
    } else {
      handle_write_char(format[i], buffer, i, width, precision, size);
      i++;
    }
  }

  va_end(list);

  return write(1, buffer, strlen(buffer));
}

int get_print_fn(char c) {
  switch (c) {
    case 'c':
      return print_char;
    case 's':
      return print_string;
    case '%':
      return print_percent;
    case 'd':
      return print_int;
    case 'o':
      return print_octal;
    case 'x':
      return print_hexadecimal;
    case 'X':
      return print_hexa_upper;
    default:
      return NULL;
  }
}

