// Top Bar
[@react.component]
let make = () => {
  <div className="top-bar">
    {"SSR SPA React Reason Native" |> React.string}
    <ul className="menu">
      <button className="button" onClick={_ => {ReasonReactRouter.push("/")}}>
        {"Home" |> React.string}
      </button>
      <button
        className="button"
        onClick={_ => {ReasonReactRouter.push("/pokemon?name=ditto")}}>
        {"Pokemon Page (Fetch from Pokemon API with getInitialProps)"
         |> React.string}
      </button>
      <button
        className="button"
        onClick={_ => {ReasonReactRouter.push("/other-page")}}>
        {"Other page (Internal api with getInitialProps)" |> React.string}
      </button>
    </ul>
  </div>;
};
