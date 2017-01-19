
export class Assignment {
  id:number = null;
  title:string = null;
  type:boolean = null;
  status:boolean = true;
  created:number = null;
  startDate:string = null;
  endDate:string = null;
  project:number = null;
  body: string = null;
  critiqueMethod:string = null;
  critiquePrivacy:boolean = null;
  critiqueStyle:string = null;
  metadata:any = {};

  constructor() {
    this.critiqueMethod = 'none'
  }
}