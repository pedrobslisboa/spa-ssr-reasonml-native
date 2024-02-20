type nodeList;
type document;

let rec joinUrlPaths = paths =>
  switch (paths) {
  | [] => "/"
  | [hd] => "/" ++ hd
  | [hd, ...tail] => hd ++ "/" ++ joinUrlPaths(tail)
  };

type routeDetails('a) = {
  route: 'a,
  initialProps: option(Js.Json.t),
};

[@react.component]
let make = (~pathMappingDetails) => {
  let url = ReasonReactRouter.useUrl();
  let (loading, setLoading) = React.useState(() => false);
  let (routeDetails, setRouteDetails) =
    React.useState(() =>
      {
        route: url.path |> joinUrlPaths,
        initialProps:
          Webapi.Dom.(
            {
              switch (document |> Document.getElementById("__DATA__")) {
              | Some(el) =>
                let data = Element.innerText(el) |> Js.Json.parseExn;

                Some(data);
              | None => None
              };
            }
          ),
      }
    );
  let (renderRouteComponent, hasInitialProps) =
    pathMappingDetails(routeDetails.route);

  React.useEffect1(
    () => {
      setLoading(_ => true);

      if (hasInitialProps) {
        Js.Promise.(
          Fetch.fetch(
            "/api/initial-props"
            ++ (url.path |> joinUrlPaths)
            ++ (
              switch (url.search) {
              | "" => ""
              | search => "?" ++ search
              }
            ),
          )
          |> then_(response =>
               try(response |> Fetch.Response.json) {
               | _ =>
                 Js.log("Error parsing JSON");
                 raise(Not_found);
               }
             )
          |> then_(props => {
               setLoading(_ => false);
               setRouteDetails(_ =>
                 {route: url.path |> joinUrlPaths, initialProps: Some(props)}
               );

               () |> resolve;
             })
          |> catch(_ => {
               setRouteDetails(_ =>
                 {route: url.path |> joinUrlPaths, initialProps: None}
               );
               setLoading(_ => false);

               () |> resolve;
             })
          |> ignore
        );
      } else {
        setLoading(_ => false);
        setRouteDetails(_ =>
          {route: url.path |> joinUrlPaths, initialProps: None}
        );
      };

      None;
    },
    [|url.path|],
  );

  React.useEffect1(
    () => {
      UniversalPortal_Shared.removeServerPortals();

      None;
    },
    [||],
  );

  <>
    {loading ? <Shared_js_demo.Loader /> : React.null}
    {renderRouteComponent(routeDetails.initialProps)}
  </>;
};
