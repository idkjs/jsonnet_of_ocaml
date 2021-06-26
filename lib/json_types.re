open Core;
open Out_channel;

type value = [
  | `Assoc(list((string, value)))
  | `Bool(bool)
  | `Float(float)
  | `Int(int)
  | `List(list(value))
  | `Null
  | `String(string)
];

let rec output_value = outc =>
  fun
  | `Assoc(obj) => print_assoc(outc, obj)
  | `List(l) => print_list(outc, l)
  | `String(s) => printf("\"%s\"", s)
  | `Int(i) => printf("%d", i)
  | `Float(x) => printf("%f", x)
  | `Bool(true) => output_string(outc, "true")
  | `Bool(false) => output_string(outc, "false")
  | `Null => output_string(outc, "null")

and print_assoc = (outc, obj) => {
  output_string(outc, "{ ");
  let sep = ref("");
  List.iter(
    ~f=
      ((key, value)) => {
        printf("%s\"%s\": %a", sep^, key, output_value, value);
        sep := ",\n  ";
      },
    obj,
  );
  output_string(outc, " }");
}

and print_list = (outc, arr) => {
  output_string(outc, "[");
  List.iteri(
    ~f=
      (i, v) => {
        if (i > 0) {
          output_string(outc, ", ");
        };
        output_value(outc, v);
      },
    arr,
  );
  output_string(outc, "]");
};
