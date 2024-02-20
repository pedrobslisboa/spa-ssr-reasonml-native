let make =
  Routes_build.make(
    ~route=Shared_native_demo.Pages_Home.route,
    ~renderApp=_ => <Shared_native_demo.Pages_Home />,
    ~initialProps=_ => Lwt.return(None),
  );
