export class Assignment {
  id: number;
  type: string;
  status: boolean;
  created: number;
  body: string;
  links: Array<string>;
  startDate: number;
  endDate: number;
  dependency: string;
  assets: Array<string>;
  critique: Array<any>;
}
