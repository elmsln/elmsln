/**
 * Copyright 2025 NazmanRosman
 * @license Apache-2.0, see LICENSE for full text.
 */
import{LitElement as e,html as t,css as i}from"../../../lit/index.js";import{DDDSuper as o}from"../../d-d-d/d-d-d.js";import{I18NMixin as r}from"../../i18n-manager/lib/I18NMixin.js";import{store as a}from"../../haxcms-elements/lib/core/haxcms-site-store.js";import{autorun as s,toJS as n}from"../../../mobx/dist/mobx.esm.js";export class GlossyPortfolioHeader extends(o(r(e))){static get tag(){return"glossy-portfolio-header"}constructor(){super(),this.title="Title",this.homeLink="",this.__disposer=this.__disposer||[],s((e=>{let t=a.getItemChildren(null);t&&t.length>0&&(this.topItems=[...t]),this.__disposer.push(e)})),s((e=>{this.homeLink=n(a.homeLink),this.__disposer.push(e)})),s((e=>{this.logo=n(a.logo),console.log(this.logo),this.__disposer.push(e)}))}static get properties(){return{...super.properties,title:{type:String},thumbnail:{type:String},link:{type:String},topItems:{type:Array}}}static get styles(){return[super.styles,i`
      :host {
        display: block;
        
        /* min-width: 400px; */
        height: auto;
        background-color: #1d1d1d;
      }

      *{
        box-sizing: border-box;
        margin: 0;
        padding: 0;
      }

      ul{
        margin: 0;
        padding: 0;
      }

      .container{
        background: linear-gradient(180deg, rgba(17, 17, 17, 1) 0%, rgba(17, 17, 17, 0) 100%);;

        display: flex;
        justify-content: space-between;
        align-items: center;
        z-index: 10;
        position: fixed;
        top: 0px;
        width: 100vw;
        position: fixed;
        left: 0;
        right: 0;
        padding: 50px 50px 40px 50px;
        /* temporary */
        margin-top: 50px;
        max-height: 80px;
        font-family: var(--main-font);  
        overflow-x: auto;
        overflow-y: hidden;

      }
      

      .nav-links li{
        font-weight: 700;
        font-family: var(--main-font);

      }
    
      .hamburger{
        width: 40px;
        height: 40px;
        display: none;
      }

      .logo{
        max-height: 60px;
        min-height: 60px;
        flex: 0 0 auto;
        position: relative;
        z-index: 10;
      }

      ul{
        display: flex;
        flex-direction: row;
        align-items: center;
        gap: 50px;
        list-style: none;
      }
      li{
        flex: 0 1 auto;
        text-align: center;
      }
      .nav-links{
        transition: all 0.3s ease-in-out;
      }
      a, div.header-link{
        all: unset;
        color: white;
        text-decoration: none;
        font-weight: 500;
        font-size: 1rem;

      }
      a .active-title, div.header-link .active-title {
        font-weight: 800;
      }
      a:hover, div.header-lik:hover{
        /* all: unset; */
        color: white;
        /* font-weight: 500; */

      }
      button{
        all: unset;
        cursor: pointer;
      }


      /* Extra small devices (phones) */
      @media (max-width: 575.98px) {
        /* Styles for phones */
        .container{
          /* padding: 15px 0px; */
          padding: 0;
          background: var(--bg-color);
          flex-wrap: wrap;
          align-items: center;
          position: fixed;
          top: 0;
          bottom: 0;
          overflow-y: scroll;
          overflow-x: hidden;
          align-content: start;
          height: 60px;

        }

        .logo-hamburger{
          display: flex;
          justify-content: space-between;
          width: 100%;
          max-height: 60px;
          flex: 0 0 auto;
        }

        /* active after hamburger is clicked */
        .container.active{
          /* padding: 15px 0 0 0; */
          height: auto;
          max-height: 100vh;
          overflow-y: scroll;
        }
        .nav-links.active{
          display: flex;
        }
        .nav-links{
          display: none;
          flex-direction: column;

          gap: 0px;
          width: 100vw;
          padding: 0;
          border-radius: 10px;

        }
        

        .hamburger{
          display: block;
          padding-right: 15px;

        }
        svg.logo{
          /* max-height: 60px; */
          max-height: 60px;
          padding-left: 15px;

        }


        /* nav links */
        li, a.right-side-item{
          display: flex;
          flex-direction: column;
          justify-content: center;
          width: 100vw;
          text-align: center; /* Centers the text horizontally */
          height: 80px;
          
        }

        a.right-side-item:active, a.right-side-item:hover{
          background-color: #1d1d1d;
          text-decoration: none; /* Ensures underline is removed on hover */

        }

        
        
      }

      /* Small devices (landscape phones, large phones) */
      @media (min-width: 576px) and (max-width: 767.98px) {
        /* Styles for small devices */
      }

      /* Medium devices (tablets) */
      @media (min-width: 768px) and (max-width: 991.98px) {
        /* Styles for tablets */
      }
      


    `]}openHamburger(){const e=this.renderRoot.querySelector(".nav-links"),t=this.renderRoot.querySelector(".container");e.classList.toggle("active"),t.classList.toggle("active")}render(){return t`
<div class="container">
  <!-- <img class="logo" src="lib/components/logo.svg" > -->
  <div class="logo-hamburger">
    <a href="${this.homeLink}">
      <img class="logo" src="${function getPostLogo(e){return e.metadata.image?e.metadata.image:a.manifest.metadata.theme.variables.image?n(a.manifest.metadata.theme.variables.image):n(a.manifest.metadata.site.logo)}(a.manifest)}" alt="Logo" />
  </a>
    <button>
      <!-- <img @click="" class="hamburger" src="../lib/components/hamburger.svg" width="70px"> -->
      <svg class="hamburger" @click="${this.openHamburger}"  width="800px" height="800px" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
        <g id="SVGRepo_bgCarrier" stroke-width="0"/>
        <g id="SVGRepo_tracerCarrier" stroke-linecap="round" stroke-linejoin="round"/>
        <g id="SVGRepo_iconCarrier"> <path d="M4 18L20 18" stroke="#ffffff" stroke-width="2" stroke-linecap="round"/> <path d="M4 12L20 12" stroke="#ffffff" stroke-width="2" stroke-linecap="round"/> <path d="M4 6L20 6" stroke="#ffffff" stroke-width="2" stroke-linecap="round"/> </g>
      </svg>
      
    </button>
  </div>
  <ul class="nav-links">
    ${Array.from(this.topItems).map((e=>t`
        <li><a class="right-side-item" href="${e.slug}"><div class="header-link ${this.toKebabCase(e.title)}">${e.title}</div></a></li>
      `))}
  </ul>
  
    
</div>
`}toKebabCase(e){return e.replace(/\s+/g,"-")}static get haxProperties(){return new URL(`./lib/${this.tag}.haxProperties.json`,import.meta.url).href}}globalThis.customElements.define(GlossyPortfolioHeader.tag,GlossyPortfolioHeader);