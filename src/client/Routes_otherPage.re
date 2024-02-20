type otherPageInitialProps = {name: string};
let otherPageInitialProps = json =>
  Json.Decode.{name: json |> field("name", string)};

[@react.component]
let make = (~initialProps) =>
  <Shared_js_demo.Pages_OtherPage
    pageProps={
      switch (initialProps) {
      | Some(props) =>
        let decodedProps: Shared_js_demo.Pages_OtherPage.props = {
          name: otherPageInitialProps(props).name,
        };

        decodedProps;
      | None => {name: "World"}
      }
    }
  />;
