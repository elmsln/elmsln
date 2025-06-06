/**
 * Copyright 2025 NazmanRosman
 * @license Apache-2.0, see LICENSE for full text.
 */
import{LitElement as t,html as i,css as e}from"../../../lit/index.js";import{DDDSuper as a}from"../../d-d-d/d-d-d.js";import{I18NMixin as r}from"../../i18n-manager/lib/I18NMixin.js";import{store as s}from"../../haxcms-elements/lib/core/haxcms-site-store.js";import{autorun as o,toJS as l}from"../../../mobx/dist/mobx.esm.js";export class GlossyPortfolioGrid extends(a(r(t))){static get tag(){return"glossy-portfolio-grid"}constructor(){super(),this.filtersList=[],this.filteredData=[],this.data=[],this.activeFilter=""}static get properties(){return{...super.properties,filteredData:{type:Array},data:{type:Array},filtersList:{type:Array}}}static get styles(){return[super.styles,e`
      :host {
        display: block;
        color: white;
      }
      *{
        box-sizing: border-box;
      }
      button {
        all: unset;
        cursor: pointer;
      }

      .container-background{
        margin: auto;
        max-width: var(--max-width); 
        background-color: var(--bg-color);

        width: 100%;
        padding: var(--page-padding);
        min-height: 100vh;
        padding-bottom: 30px;
      }
      .projects-header{
        display: flex;
        justify-content: space-between;
        padding: 50px 0;
        max-width: 100%;
      }
      .grid-title{
        font-size: 1rem;
        font-weight: 800;
        letter-spacing: 1.7px;

      }
      .filters{
        display: flex;
        gap: 16px;
        flex-wrap: wrap;

      }
      .filters:hover{
        cursor: pointer;

      }

      .filter{
        font-family: "Inter", "Inter Placeholder", sans-serif;
        font-size: 1rem;
        color: rgb(153, 153, 153);
      }
      .card-container {
        display: grid;
        /* border: 1px solid red; */
        grid-template-columns: repeat(2, minmax(200px, 1fr));
        gap: 45px;
        justify-content: center;
        /* width: 100vw; */
        overflow: hidden;
        max-width: var(--max-width); 
      }

      glossy-portfolio-card{
        height: auto;
      }


      h3 span {
        font-size: var(--glossy-portfolio-label-font-size, var(--ddd-font-size-s));
      }
      .filter.active {
        font-weight: bold;
      }

      @media (max-width: 575.98px) {
        .projects-header{
          flex-direction: column;
          gap: 16px;
          padding: 50px 0 20px 0;
        }
        .card-container {
         grid-template-columns: 1fr;
         gap: 25px;

        }
        .container-background{
          padding: var(--mobile-page-padding);

        }
      }

    `]}render(){return i`
          
<div class = "container-background">
  <div class="projects-header">

    <div class="grid-title">${this.title.toUpperCase()}</div>
    <div class="filters">
      <button class="filter active" name="all" @click="${this.updateFilter}">All</button>
      
        <!-- print filters -->
      ${Array.from(this.filtersList).map((t=>i`
        <button @click="${this.updateFilter}" name="${t}"  class="filter"> 
          ${this.capitalizeWords(t)} 
      </button>
      `))}

    </div>

  </div>
  <div class="card-container">
    ${this.filteredData.map((t=>i`
        <glossy-portfolio-card class="card" 
        title="${t.title}" 
        thumbnail=${t.metadata.images[0]?t.metadata.images[0]:"https://img.freepik.com/premium-photo/cool-cat-wearing-pink-sunglasses-with-neon-light-background_514761-16858.jpg"}
        slug="${t.slug}"
        >
      </glossy-portfolio-card>
      `))}
    </div> 
</div> 

`}capitalizeWords(t){return t.split(" ").map((t=>t.charAt(0).toUpperCase()+t.slice(1))).join(" ")}updated(t){super.updated(t),t.has("data")&&this.data&&this.data.length>0&&(this.filteredData=this.data,this.filtersList=[],this.data.forEach((t=>{if(void 0!==t.metadata.tags&&null!==t.metadata.tags&&t.metadata.tags.split(",").length>0){const i=t.metadata.tags.split(",")[0];this.filtersList.includes(i)||this.filtersList.push(i)}})))}_updateFilter(t,i){this.activeFilter=t.getAttribute("name");this.renderRoot.querySelectorAll(".filter").forEach((t=>t.classList.remove("active"))),i.classList.add("active"),this.filterData()}updateFilter(t){const i=t.target,e=t.currentTarget;globalThis.document.startViewTransition?globalThis.document.startViewTransition((()=>{this._updateFilter(i,e)})):this._updateFilter(i,e)}filterData(){"all"===this.activeFilter?this.filteredData=this.data:(this.filteredData=[],this.data.forEach((t=>{t.metadata.tags&&t.metadata.tags.includes(this.activeFilter)&&this.filteredData.push(t)})))}static get haxProperties(){return new URL(`./lib/${this.tag}.haxProperties.json`,import.meta.url).href}}globalThis.customElements.define(GlossyPortfolioGrid.tag,GlossyPortfolioGrid);