open Lwt;

let indexFile = open_in_bin("./public/index.html");
let indexFileString =
  really_input_string(indexFile, in_channel_length(indexFile));

let make = (~route, ~renderApp, ~initialProps) => [
  Dream.get(
    route,
    req => {
      let portals: ref(array(UniversalPortal_Shared.portal)) = ref([||]);

      initialProps(req)
      >>= (
        initialPropsOption => {
          switch (initialPropsOption) {
          | Some(props) =>
            let html =
              ReactDOM.renderToString(
                UniversalPortal_Server.collectPortals(
                  renderApp(props),
                  (collectedPortal: UniversalPortal_Shared.portal) => {
                  portals := Array.append(portals^, [|collectedPortal|])
                }),
              );

            Str.global_replace(
              Str.regexp("<div id=\"root\"></div>"),
              "<div id=\"root\">"
              ++ html
              ++ "</div><script id=\"__DATA__\" type=\"application/json\">"
              ++ Yojson.Basic.to_string(props)
              ++ "</script>",
              indexFileString,
            )
            |> UniversalPortal_Server.appendUniversalPortals(_, portals^)
            |> Dream.html;
          | None =>
            let html =
              ReactDOM.renderToString(
                UniversalPortal_Server.collectPortals(
                  renderApp(Yojson.Basic.from_string("{}")),
                  (collectedPortal: UniversalPortal_Shared.portal) => {
                  portals := Array.append(portals^, [|collectedPortal|])
                }),
              );
            Str.global_replace(
              Str.regexp("<div id=\"root\"></div>"),
              "<div id=\"root\">"
              ++ html
              ++ "</div><script id=\"__DATA__\" type=\"application/json\">{}</script>",
              indexFileString,
            )
            |> UniversalPortal_Server.appendUniversalPortals(_, portals^)
            |> Dream.html;
          };
        }
      );
    },
  ),
  Dream.get("/api/initial-props" ++ route, request => {
    initialProps(request)
    >>= (
      initialProps =>
        switch (initialProps) {
        | None => Dream.json("null")
        | Some(initialProps) =>
          Yojson.Basic.to_string(initialProps) |> Dream.json
        }
    )
  }),
];
