let hasInitialProps = false;
let route = "/";

[@react.component]
let make = () => {
  let (modalOpen, setModalOpen) = React.useState(_ => true);

  <Layout>
    <UniversalPortal_Shared.Portal selector="head">
      <title> {"Home " |> React.string} </title>
    </UniversalPortal_Shared.Portal>
    <button onClick={_ => setModalOpen(_ => true)}>
      {"Open modal" |> React.string}
    </button>
    {modalOpen
       ? <UniversalPortal_Shared.Portal selector="body">
           <div className="modal">
             <div className="modal-content">
               {"Hey, I'm a universal portal, disable JS on your dev tools and check that I'll still here"
                |> React.string}
               <button onClick={_ => setModalOpen(_ => false)}>
                 {"Close" |> React.string}
               </button>
             </div>
           </div>
         </UniversalPortal_Shared.Portal>
       : React.null}
  </Layout>;
};
