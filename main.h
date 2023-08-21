int _printf(const char *format, ...) {
  va_list list;
  char buffer[BUFF_SIZE];
  int i = 0;
  int flags = 0;
  int width = 0;
  int precision = -1;
  int size = 0;

  va_start(list, format);

  while (format[i]) {
    if (format[i] == '%') {
      i++;
      flags = get_flags(format, &i);
      width = get_width(format, &i, list);
      precision = get_precision(format, &i, list);
      size = get_size(format, &i);

      va_arg(list, int);

      switch (format[i]) {
        case 'c':
          print_char(list, buffer, flags, width, precision, size);
          break;
        case 's':
          print_string(list, buffer, flags, width, precision, size);
          break;
        case '%':
          print_percent(list, buffer, flags, width, precision, size);
          break;
        case 'd':
          print_int(list, buffer, flags, width, precision, size);
          break;
        case 'o':
          print_octal(list, buffer, flags, width, precision, size);
          break;
        case 'x':
          print_hexadecimal(list, buffer, flags, width, precision, size);
          break;
        case 'X':
          print_hexa_upper(list, buffer, flags, width, precision, size);
          break;
        default:
          break;
      }

      i++;
    } else {
      handle_write_char(format[i], buffer, flags, width, precision, size);
      i++;
    }
  }

  va_end(list);

  return write(1, buffer, strlen(buffer));
}

