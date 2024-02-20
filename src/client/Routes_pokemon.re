let decodeDreamWorld: Js.Json.t => Shared_js_demo.Pages_Pokemon.dreamWorld =
  json =>
    Json.Decode.{front_default: json |> field("front_default", string)};

let decodeOther: Js.Json.t => Shared_js_demo.Pages_Pokemon.other =
  json =>
    Json.Decode.{
      dream_world: json |> field("dream_world", decodeDreamWorld),
    };

let decodeSprite: Js.Json.t => Shared_js_demo.Pages_Pokemon.sprites =
  json => Json.Decode.{other: json |> field("other", decodeOther)};

let decodeAbility: Js.Json.t => Shared_js_demo.Pages_Pokemon.ability =
  json => Json.Decode.{name: json |> field("name", string)};

let decodeAbilityRecord:
  Js.Json.t => Shared_js_demo.Pages_Pokemon.abilityRecord =
  json => Json.Decode.{ability: json |> field("ability", decodeAbility)};

let decodedProps: Js.Json.t => Shared_js_demo.Pages_Pokemon.props =
  json => {
    name: json |> Json.Decode.field("name", Json.Decode.string),
    sprites: json |> Json.Decode.field("sprites", decodeSprite),
    abilities:
      json
      |> Json.Decode.field(
           "abilities",
           Json.Decode.list(decodeAbilityRecord),
         ),
  };

[@react.component]
let make = (~initialProps) =>
  <Shared_js_demo.Pages_Pokemon
    pageProps={
      switch (initialProps) {
      | Some(props) => decodedProps(props)
      | None => {
          name: "bulbasaur",
          sprites: {
            other: {
              dream_world: {
                front_default: "https://raw.githubusercontent.com/PokeAPI/sprites/master/sprites/pokemon/other/official-artwork/1.png",
              },
            },
          },
          abilities: [
            {
              ability: {
                name: "overgrow",
              },
            },
            {
              ability: {
                name: "chlorophyll",
              },
            },
          ],
        }
      }
    }
  />;
