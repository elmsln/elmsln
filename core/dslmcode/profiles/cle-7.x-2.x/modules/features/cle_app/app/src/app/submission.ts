export class Submission {
  public id: number;
  public authorId: number;
  public assignmentId: number;

  constructor(
    public body: string,
  ) {  }
}