export class Assignment {
  id: number;
  title: string;
  type: string;
  status: boolean;
  created: number;
  body: string;
  links: Array<string>;
  startDate: string;
  endDate: string;
  dependency: string;
  assets: Array<string>;
  critique: Array<any>;
}
