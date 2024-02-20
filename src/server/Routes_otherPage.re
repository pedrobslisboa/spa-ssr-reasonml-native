let getInitialProps = _ =>
  Lwt.return(Some("{name: \"Pedro\"}" |> Yojson.Basic.from_string));

let make =
  Routes_build.make(
    ~route=Shared_native_demo.Pages_OtherPage.route,
    ~renderApp=
      initialProps => {
        <Shared_native_demo.Pages_OtherPage
          pageProps={
            name:
              initialProps
              |> Yojson.Basic.Util.member("name")
              |> Yojson.Basic.Util.to_string,
          }
        />
      },
    ~initialProps=getInitialProps,
  );
