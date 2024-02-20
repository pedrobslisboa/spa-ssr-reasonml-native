type props = {name: string};

let hasInitialProps = true;
let route = "/other-page";

[@react.component]
let make = (~pageProps) => {
  <Layout>
    <UniversalPortal_Shared.Portal selector="head">
      <title> {"Hello " ++ pageProps.name ++ "!" |> React.string} </title>
    </UniversalPortal_Shared.Portal>
    {"Hello " ++ pageProps.name |> React.string}
  </Layout>;
};
