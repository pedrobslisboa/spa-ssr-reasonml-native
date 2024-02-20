module Main = {
  [@react.component]
  let make = () => {
    <Routes_handler
      pathMappingDetails={path =>
        switch (path) {
        | route when route == Shared_js_demo.Pages_Home.route => (
            (_ => <Routes_home />),
            Shared_js_demo.Pages_Home.hasInitialProps,
          )
        | route when route == Shared_js_demo.Pages_OtherPage.route => (
            (initialProps => <Routes_otherPage initialProps />),
            Shared_js_demo.Pages_OtherPage.hasInitialProps,
          )
        | route when route == Shared_js_demo.Pages_Pokemon.route => (
            (initialProps => <Routes_pokemon initialProps />),
            Shared_js_demo.Pages_Pokemon.hasInitialProps,
          )
        | _ => (
            (_ => <Routes_home />),
            Shared_js_demo.Pages_Home.hasInitialProps,
          )
        }
      }
    />;
  };
};

switch (ReactDOM.querySelector("#root")) {
| Some(el) => <Main /> |> ReactDOM.hydrate(_, el)
| None => ()
};
