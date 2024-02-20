type dreamWorld = {front_default: string};

type other = {dream_world: dreamWorld};

type sprites = {other};

type ability = {name: string};

type abilityRecord = {ability};

type props = {
  name: string,
  sprites,
  abilities: list(abilityRecord),
};

let hasInitialProps = true;
let route = "/pokemon";

[@react.component]
let make = (~pageProps) => {
  <Layout>
    <UniversalPortal_Shared.Portal selector="head">
      <title> {"Pokemon: " ++ pageProps.name ++ "" |> React.string} </title>
    </UniversalPortal_Shared.Portal>
    <div className="pokemon">
      <div className="pokemon-card">
        <h1> {pageProps.name |> React.string} </h1>
        <img
          className="image"
          src={pageProps.sprites.other.dream_world.front_default}
          alt={pageProps.name}
        />
        <ul className="abilities">
          {pageProps.abilities
           ->Belt.List.map(ability => {
               <li className="ability" key={ability.ability.name}>
                 {ability.ability.name |> React.string}
               </li>
             })
           ->Array.of_list
           ->React.array}
        </ul>
      </div>
    </div>
  </Layout>;
};
