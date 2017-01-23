export class Submission {
  id:number = null;
  uid:number = null;
  title:string = null;
  status:boolean = true;
  created:number = null;
  body:string = null;
  assignment:number = null;
  state:string = 'submission_in_progress';
  metadata:any = {};
  environment:any = {};
  evidence:any = {};
}