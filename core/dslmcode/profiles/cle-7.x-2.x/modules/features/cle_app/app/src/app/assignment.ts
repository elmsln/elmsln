
export class Assignment {
  id:number = null;
  title:string = null;
  type:boolean = null;
  status:boolean = true;
  created:number = null;
  startDate:string = null;
  endDate:string = null;
  allowLateSubmissions: boolean = false;
  project:number = null;
  body: string = null;
  critiqueMethod:string = 'none';
  critiquePrivacy:boolean = null;
  critiqueStyle:string = null;
  metadata:any = {};
}