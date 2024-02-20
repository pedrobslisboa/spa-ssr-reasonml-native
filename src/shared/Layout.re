[@react.component]
let make = (~children) => {
  <div className="layout">
    <TopBar />
    <div className="content"> children </div>
  </div>;
};
