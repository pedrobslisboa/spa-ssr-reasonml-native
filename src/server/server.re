let routes =
  List.concat([Routes_otherPage.make, Routes_home.make, Routes_pokemon.make]);

let handler =
  Dream.router([
    Dream.get("/public/**", Dream.static("./public")),
    ...routes,
  ]);

let interface =
  switch (Sys.getenv_opt("SERVER_INTERFACE")) {
  | Some(env) => env
  | None => "localhost"
  };

Dream.run(~port=8000, ~interface, handler);
