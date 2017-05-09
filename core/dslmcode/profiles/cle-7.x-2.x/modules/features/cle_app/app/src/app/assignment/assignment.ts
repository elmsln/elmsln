export class Assignment {
  id:number = null;
  title:string = null;
  type:string = 'open';
  status:boolean = true;
  created:number = null;
  startDate:string = null;
  endDate:string = null;
  allowLateSubmissions: boolean = true;
  project:number = null;
  body: string = null;
  critiqueMethod:string = 'none';
  critiquePrivacy:boolean = false;
  metadata:any = {};
  hierarchy:any = {};
}