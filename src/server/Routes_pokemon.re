open Lwt;
open Cohttp_lwt_unix;
open Yojson.Basic.Util;

let name = json => json |> member("name") |> to_string;
let sprites = json => {
  `Assoc([
    (
      "other",
      `Assoc([
        (
          "dream_world",
          `Assoc([
            (
              "front_default",
              `String(
                json
                |> member("sprites")
                |> member("other")
                |> member("dream_world")
                |> member("front_default")
                |> to_string,
              ),
            ),
          ]),
        ),
      ]),
    ),
  ]);
};

let abilities = json => {
  `List(
    {
      json
      |> member("abilities")
      |> to_list
      |> List.map(abil => {
           `Assoc([
             (
               "ability",
               `Assoc([
                 (
                   "name",
                   `String(
                     abil |> member("ability") |> member("name") |> to_string,
                   ),
                 ),
               ]),
             ),
           ])
         });
    },
  );
};

let extractSprites =
    (json: Yojson.Basic.t): Shared_native_demo.Pages_Pokemon.sprites => {
  let front_default_url =
    json
    |> member("sprites")
    |> member("other")
    |> member("dream_world")
    |> member("front_default")
    |> to_string;

  {
    other: {
      dream_world: {
        front_default: front_default_url,
      },
    },
  };
};

let extractAbilities =
    (json: Yojson.Basic.t)
    : list(Shared_native_demo.Pages_Pokemon.abilityRecord) => {
  json
  |> member("abilities")
  |> to_list
  |> List.map(abil => {
       let value: Shared_native_demo.Pages_Pokemon.abilityRecord = {
         ability: {
           name: abil |> member("ability") |> member("name") |> to_string,
         },
       };

       value;
     });
};

let resultJson = json =>
  `Assoc([
    ("name", `String(name(json))),
    ("sprites", sprites(json)),
    ("abilities", abilities(json)),
  ]);

let resultJsonToRecord =
    (json: Yojson.Basic.t): Shared_native_demo.Pages_Pokemon.props => {
  let name = json |> member("name") |> to_string;
  let sprites = json |> extractSprites;
  let abilities = json |> extractAbilities;

  {name, sprites, abilities};
};

let getInitialProps = req => {
  let name =
    switch (Dream.query(req, "name")) {
    | Some(name) => name
    | None => "bulbasaur"
    };
  let uri = Uri.of_string("https://pokeapi.co/api/v2/pokemon/" ++ name);
  Client.get(uri)
  >>= (
    ((_, body)) => {
      body
      |> Cohttp_lwt.Body.to_string
      >|= (
        body => {
          let json = Yojson.Basic.from_string(body);

          Some(resultJson(json));
        }
      );
    }
  );
};

let make =
  Routes_build.make(
    ~route=Shared_native_demo.Pages_Pokemon.route,
    ~renderApp=
      initialProps => {
        <Shared_native_demo.Pages_Pokemon
          pageProps={initialProps |> resultJson |> resultJsonToRecord}
        />
      },
    ~initialProps=getInitialProps,
  );
