export class Critique {
  public id: number;
  public authorId: number;
  public submissionId: number;

  constructor(
    public body: string,
  ) {  }
}